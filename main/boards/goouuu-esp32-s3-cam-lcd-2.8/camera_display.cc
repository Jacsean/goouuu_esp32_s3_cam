#include "camera_display.h"
#include "esp_imgfx_color_convert.h" // 项目图像格式转换库
#include "esp_log.h"
#include "lvgl.h"
#include "esp32_camera.h"      // 确保引入项目摄像头类头文件
#include "lcd_display.h"       // 确保引入LCD显示类头文件
#include "jpg/jpeg_to_image.h" // 添加JPEG解码所需头文件

static const char *TAG = "CameraDisplay";

// 构造函数
CameraDisplay::CameraDisplay(Esp32Camera *camera, LcdDisplay *display)
    : camera_(camera), display_(display), display_task_handle_(nullptr), is_running_(false)
{
    ESP_LOGI(TAG, "CameraDisplay initialized");
}

// 析构函数
CameraDisplay::~CameraDisplay()
{
    Stop();
}

// JPEG转RGB565（适配ILI9341显示格式）
uint8_t *CameraDisplay::ConvertJPEGToRGB565(const uint8_t *jpeg_data, size_t jpeg_len, uint16_t *out_width, uint16_t *out_height)
{
    uint8_t *rgb_data = nullptr;
    size_t rgb_len = 0;
    size_t width = 0;
    size_t height = 0;
    size_t stride = 0;

    esp_err_t ret = jpeg_to_image(jpeg_data, jpeg_len, &rgb_data, &rgb_len, &width, &height, &stride);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to decode JPEG image: %d (%s)", (int)ret, esp_err_to_name(ret));
        if (rgb_data)
        {
            heap_caps_free(rgb_data);
        }
        return nullptr;
    }

    *out_width = width;
    *out_height = height;
    return rgb_data;
}

// YUV转RGB565（适配ILI9341显示格式）
uint8_t* CameraDisplay::ConvertYUVToRGB565(const uint8_t* yuv_data, uint16_t width, uint16_t height) {
    // 使用更小的尺寸以节省内存 (1/8的宽高，即原尺寸的1/64)
    uint16_t target_width = width / 8;
    uint16_t target_height = height / 8;
    
    // 直接为目标尺寸分配内存
    size_t rgb_size = target_width * target_height * 2; // RGB565每个像素2字节
    uint8_t* rgb_data = (uint8_t*)heap_caps_malloc(rgb_size, MALLOC_CAP_SPIRAM);

    if (!rgb_data) {
        ESP_LOGE(TAG, "Failed to allocate memory for RGB data");
        return nullptr;
    }

    // 分块处理，每次只处理一小部分数据以减少内存峰值
    // 创建临时缓冲区用于YUV到RGB的转换（只需要一行）
    size_t yuv_line_size = width * 2; // YUV422格式，每行字节数
    uint8_t* temp_yuv_line = (uint8_t*)malloc(yuv_line_size);
    if (!temp_yuv_line) {
        ESP_LOGE(TAG, "Failed to allocate temporary buffer for YUV line data");
        heap_caps_free(rgb_data);
        return nullptr;
    }
    
    uint8_t* temp_rgb_line = (uint8_t*)malloc(width * 2); // 临时RGB行缓冲区
    if (!temp_rgb_line) {
        ESP_LOGE(TAG, "Failed to allocate temporary buffer for RGB line data");
        free(temp_yuv_line);
        heap_caps_free(rgb_data);
        return nullptr;
    }

    // 逐行处理并下采样
    for (uint16_t ty = 0; ty < target_height; ty++) {
        // 计算源图像中的行号（每隔8行取一行）
        uint16_t sy = ty * 8;
        
        // 拷贝YUV数据的一行到临时缓冲区
        memcpy(temp_yuv_line, yuv_data + (sy * yuv_line_size), yuv_line_size);
        
        // 创建颜色转换配置
        esp_imgfx_color_convert_cfg_t convert_cfg = {
            .in_res = {.width = static_cast<int16_t>(width),
                       .height = 1}, // 只转换一行
            .in_pixel_fmt = ESP_IMGFX_PIXEL_FMT_YUYV,
            .out_pixel_fmt = ESP_IMGFX_PIXEL_FMT_RGB565_LE,
            .color_space_std = ESP_IMGFX_COLOR_SPACE_STD_BT601,
        };
        
        esp_imgfx_color_convert_handle_t convert_handle = nullptr;
        esp_imgfx_err_t err = esp_imgfx_color_convert_open(&convert_cfg, &convert_handle);
        if (err != ESP_IMGFX_ERR_OK || convert_handle == nullptr) {
            ESP_LOGE(TAG, "esp_imgfx_color_convert_open failed");
            free(temp_rgb_line);
            free(temp_yuv_line);
            heap_caps_free(rgb_data);
            return nullptr;
        }
        
        esp_imgfx_data_t convert_input_data = {
            .data = temp_yuv_line,
            .data_len = yuv_line_size,
        };
        
        esp_imgfx_data_t convert_output_data = {
            .data = temp_rgb_line,
            .data_len = static_cast<uint32_t>(width * 2),
        };
        
        err = esp_imgfx_color_convert_process(convert_handle, &convert_input_data, &convert_output_data);
        esp_imgfx_color_convert_close(convert_handle);
        
        if (err != ESP_IMGFX_ERR_OK) {
            ESP_LOGE(TAG, "Color conversion failed: %d", err);
            free(temp_rgb_line);
            free(temp_yuv_line);
            heap_caps_free(rgb_data);
            return nullptr;
        }
        
        // 下采样并将结果写入目标图像
        uint16_t* src_line = (uint16_t*)temp_rgb_line;
        uint16_t* dst_line = (uint16_t*)rgb_data + (ty * target_width);
        
        for (uint16_t tx = 0; tx < target_width; tx++) {
            uint16_t sx = tx * 8; // 每隔8个像素取一个
            dst_line[tx] = src_line[sx];
        }
    }
    
    // 释放临时缓冲区
    free(temp_rgb_line);
    free(temp_yuv_line);
    
    return rgb_data;
}

// 核心：修正后的显示任务（移除FrameBuffer，改用项目真实接口）
void CameraDisplay::DisplayTask(void *arg)
{
    CameraDisplay *instance = static_cast<CameraDisplay *>(arg);
    ESP_LOGI(TAG, "Display task started");

    while (instance->is_running_)
    {
        // 1. 采集一帧图像（项目Esp32Camera的Capture()方法）
        if (!instance->camera_->Capture())
        {
            ESP_LOGE(TAG, "Failed to capture frame");
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        // 2. 获取帧数据（改用项目真实接口）
        const uint8_t *frame_data = instance->camera_->GetFrameData();     // 获取帧数据
        size_t frame_len = instance->camera_->GetFrameLength();            // 获取帧长度
        uint16_t frame_width = instance->camera_->GetFrameWidth();         // 获取帧宽度
        uint16_t frame_height = instance->camera_->GetFrameHeight();       // 获取帧高度
        v4l2_pix_fmt_t frame_format = instance->camera_->GetFrameFormat(); // 获取帧格式

        // 3. 校验帧数据有效性
        if (!frame_data || frame_len == 0)
        {
            ESP_LOGE(TAG, "Invalid frame data");
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        // 4. 根据帧格式进行不同处理
        uint8_t *display_data = nullptr;
        uint16_t display_width = 0;
        uint16_t display_height = 0;

        if (frame_format == V4L2_PIX_FMT_JPEG)
        {
            // JPEG格式需要解码
            display_data = instance->ConvertJPEGToRGB565(frame_data, frame_len, &display_width, &display_height);
            if (!display_data)
            {
                vTaskDelay(pdMS_TO_TICKS(100));
                continue;
            }
            ESP_LOGD(TAG, "Converted JPEG to RGB: %dx%d", display_width, display_height);
        }
        else if (frame_format == V4L2_PIX_FMT_YUYV)
        {
            // YUV格式需要转换并降低分辨率
            display_data = instance->ConvertYUVToRGB565(frame_data, frame_width, frame_height);
            if (!display_data)
            {
                vTaskDelay(pdMS_TO_TICKS(100));
                continue;
            }
            display_width = frame_width / 2;
            display_height = frame_height / 2;
            ESP_LOGD(TAG, "Converted YUV to RGB: %dx%d", display_width, display_height);
        }
        else
        {
            ESP_LOGE(TAG, "Unsupported frame format: 0x%08x", frame_format);
            vTaskDelay(pdMS_TO_TICKS(100));
            continue;
        }

        // 5. 刷新到ILI9341显示屏
        instance->display_->UpdatePreview(display_data, display_width, display_height);

        // 6. 释放临时内存（避免内存泄漏）
        heap_caps_free(display_data);

        // 7. 控制帧率（约30fps，平衡流畅度与CPU占用）
        vTaskDelay(pdMS_TO_TICKS(33));

        // 8. LVGL UI刷新（必须调用，否则屏幕无更新）
        lv_task_handler();
    }

    ESP_LOGI(TAG, "Display task stopped");
    vTaskDelete(nullptr);
}

// 启动显示任务
bool CameraDisplay::Start()
{
    if (is_running_)
    {
        ESP_LOGW(TAG, "Display is already running");
        return true;
    }

    is_running_ = true;
    // 创建FreeRTOS任务（绑定到核心1，避开WiFi/蓝牙核心0）
    BaseType_t ret = xTaskCreatePinnedToCore(
        DisplayTask,
        "camera_display",
        8192, // 增大栈空间（4096可能不足，改为8192）
        this,
        5, // 任务优先级（中等，避免抢占系统任务）
        &display_task_handle_,
        1);

    if (ret != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create display task");
        is_running_ = false;
        display_task_handle_ = nullptr;
        return false;
    }

    return true;
}

// 停止显示任务
void CameraDisplay::Stop()
{
    if (!is_running_)
        return;

    is_running_ = false;
    if (display_task_handle_)
    {
        // 等待任务退出（超时1秒）
        xTaskNotifyWait(0, 0, nullptr, pdMS_TO_TICKS(1000));
        display_task_handle_ = nullptr;
    }
}