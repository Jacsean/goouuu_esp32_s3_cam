#pragma once
#include "esp32_camera.h"
#include "lcd_display.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstdint>

// 前置声明，避免循环依赖
class Esp32Camera;
class LcdDisplay;

// 相机显示类
class CameraDisplay {
private:
    Esp32Camera* camera_;
    LcdDisplay* display_;
    TaskHandle_t display_task_handle_;
    bool is_running_;

    // 图像格式转换
    uint8_t* ConvertYUVToRGB565(const uint8_t* yuv_data, uint16_t width, uint16_t height);
    uint8_t* ConvertJPEGToRGB565(const uint8_t* jpeg_data, size_t jpeg_len, uint16_t* out_width, uint16_t* out_height);
    
    // 任务函数
    static void DisplayTask(void* arg);

public:
    CameraDisplay(Esp32Camera* camera, LcdDisplay* display);
    ~CameraDisplay();

    // 启动显示任务
    bool Start();
    
    // 停止显示任务
    void Stop();
    
    // 获取运行状态
    bool IsRunning() const { return is_running_; }
};