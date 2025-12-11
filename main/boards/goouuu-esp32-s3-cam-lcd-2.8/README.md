硬件基于基于ESP32S3CAM开发板，代码基于bread-compact-wifi-lcd修改
使用的摄像头是OV2640
注意因为摄像头占用IO较多，所以占用了ESP32S3的USB 19 20两个引脚
连线方式参考config.h文件中对引脚的定义

```C++

/*
--- config.h
    board pin configuration for Goouuu ESP32-S3-CAM-LCD-2.8-v1.2

    Esp32-S3-CAM        Camera          LCDili9341          AUDIO               Other
    GPIO_0              X               PIN_BACKLIGHT/LED   X                   X
    GPIO_1              X               X                   I2S_MIC_WS          X
    GPIO_2              X               X                   I2S_MIC_SCK         X
    GPIO_3              X               PIN_CLK/SCK         X                   X
    GPIO_4              PIN_SIOD        X                   X                   X
    GPIO_5              PIN_SIOC        X                   X                   X
    GPIO_6              PIN_VSYNC       X                   X                   X
    GPIO_7              PIN_HREF        X                   X                   X
    GPIO_8              PIN_D2          X                   X                   X
    GPIO_9              PIN_D1          X                   X                   X
    GPIO_10             PIN_D3          X                   X                   X
    GPIO_11             PIN_D0          X                   X                   X
    GPIO_12             PIN_D4          X                   X                   X
    GPIO_13             PIN_PCLK        X                   X                   X
    GPIO_14             X               PIN_CS              X                   X
    GPIO_15             PIN_XCLK        X                   X                   X
    GPIO_16             PIN_D7          X                   X                   X
    GPIO_17             PIN_D6          X                   X                   X
    GPIO_18             PIN_D5          X                   X                   X
    GPIO_19             X               X                   X                   BUTTON_BOOT
    GPIO_21             X               PIN_RST             X                   X
    GPIO_35             X               X                   X                   BUTTON_VOLUME_UP
    GPIO_36             X               X                   X                   BUTTON_VOLUME_DOWN
    GPIO_37             X               X                   X                   X
    GPIO_38             X               X                   X                   X
    GPIO_39             X               X                   I2S_SPK_DOUT        X
    GPIO_40             X               X                   I2S_SPK_BCLK        X
    GPIO_41             X               X                   I2S_SPK_LRCK        X
    GPIO_42             X               X                   I2S_MIC_DIN         X
    GPIO_43             X               X                   X                   X
    GPIO_44             X               X                   X                   X
    GPIO_45             X               PIN_MOSI/SDI        X                   X
    GPIO_46             X               PIN_MISO/SDO        X                   X
    GPIO_47             X               PIN_DC              X                   X
    GPIO_48             X               X                   X                   BUILTIN_LED
    GPIO_NC             PIN_PWDN        X                   X                   X
    GPIO_NC             PIN_RESET       X                   X                   X
    GPIO_NC             X               X                   X                   BUTTON_TOUCH

*/
```

# 编译配置命令

**配置编译目标为 ESP32S3：**

```bash
idf.py set-target esp32s3
```

**打开 menuconfig：**

```bash
idf.py menuconfig
```

**选择板子：**

```bash
Xiaozhi Assistant -> Board Type ->面包板新版接线（WiFi）+ LCD + Camera
```

**配置摄像头传感器：**

> **注意：** 确认摄像头传感器型号，确定型号在 esp_cam_sensor 支持的范围内。当前板子用的是 OV2640，是符合支持范围。

在 menuconfig 中按以下步骤启用对应型号的支持：

1. **导航到传感器配置：**

   ```
   (Top) → Component config → Espressif Camera Sensors Configurations → Camera Sensor Configuration → Select and Set Camera Sensor
   ```
2. **选择传感器型号：**

   - 选中所需的传感器型号（OV2640）
3. **配置传感器参数：**

   - 按 → 进入传感器详细设置
   - 启用 **Auto detect**
   - 推荐将 **default output format** 调整为 **YUV422** 及合适的分辨率大小
   - （目前支持 YUV422、RGB565，YUV422 更节省内存空间）

**编译烧入：**

```bash
idf.py build flash
```
