/* 
    board pin configuration for Goouuu ESP32-S3-CAM-LCD-2.8 

    Esp32-S3-CAM        Camera          LCDili9341          AUDIO               Other
    GPIO_0              X               PIN_BACKLIGHT       X                   X
    GPIO_1              X               X                   I2S_MIC_WS          X
    GPIO_2              X               X                   I2S_MIC_SCK         X
    GPIO_3              X               PIN_CLK             X                   X
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
    GPIO_45             X               PIN_MOSI            X                   X   
    GPIO_46             X               X                   X                   X
    GPIO_47             X               PIN_DC              X                   X
    GPIO_48             X               X                   X                   BUILTIN_LED
    GPIO_NC             PIN_PWDN        X                   X                   X
    GPIO_NC             PIN_RESET       X                   X                   X
    GPIO_NC             X               X                   X                   BUTTON_TOUCH

*/

#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

#define AUDIO_INPUT_SAMPLE_RATE  16000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// 如果使用 Duplex I2S 模式，请注释下面一行
#define AUDIO_I2S_METHOD_SIMPLEX

#ifdef AUDIO_I2S_METHOD_SIMPLEX

#define AUDIO_I2S_MIC_GPIO_WS   GPIO_NUM_1
#define AUDIO_I2S_MIC_GPIO_SCK  GPIO_NUM_2
#define AUDIO_I2S_MIC_GPIO_DIN  GPIO_NUM_42
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_39
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_40
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_41

#else

#define AUDIO_I2S_GPIO_WS GPIO_NUM_4
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_5
#define AUDIO_I2S_GPIO_DIN  GPIO_NUM_6
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_7

#endif


// A MCP Test: Control a lamp
// #define LAMP_GPIO GPIO_NUM_14


#define BUILTIN_LED_GPIO        GPIO_NUM_48 // 内置LED
#define BOOT_BUTTON_GPIO        GPIO_NUM_19 // boot、唤醒、打断
#define TOUCH_BUTTON_GPIO       GPIO_NUM_NC //
#define VOLUME_UP_BUTTON_GPIO   GPIO_NUM_35 // 音量赠
#define VOLUME_DOWN_BUTTON_GPIO GPIO_NUM_36 // 音量减

//Camera Config
#define CAMERA_PIN_D0 GPIO_NUM_11
#define CAMERA_PIN_D1 GPIO_NUM_9
#define CAMERA_PIN_D2 GPIO_NUM_8
#define CAMERA_PIN_D3 GPIO_NUM_10
#define CAMERA_PIN_D4 GPIO_NUM_12
#define CAMERA_PIN_D5 GPIO_NUM_18
#define CAMERA_PIN_D6 GPIO_NUM_17
#define CAMERA_PIN_D7 GPIO_NUM_16
#define CAMERA_PIN_XCLK GPIO_NUM_15
#define CAMERA_PIN_PCLK GPIO_NUM_13
#define CAMERA_PIN_VSYNC GPIO_NUM_6
#define CAMERA_PIN_HREF GPIO_NUM_7
#define CAMERA_PIN_SIOC GPIO_NUM_5
#define CAMERA_PIN_SIOD GPIO_NUM_4
#define CAMERA_PIN_PWDN GPIO_NUM_NC
#define CAMERA_PIN_RESET GPIO_NUM_NC
#define XCLK_FREQ_HZ 20000000

// ILI9341 PIN Config
#define DISPLAY_BACKLIGHT_PIN GPIO_NUM_0    //
#define DISPLAY_MOSI_PIN      GPIO_NUM_45   //
#define DISPLAY_CLK_PIN       GPIO_NUM_3    //
#define DISPLAY_RST_PIN       GPIO_NUM_21
#define DISPLAY_DC_PIN        GPIO_NUM_47
#define DISPLAY_CS_PIN        GPIO_NUM_14   //

#ifdef CONFIG_GOOUUU_ESP32_S3_CAM_V1_2_LCD_ILI9341_NO_IPS
#define LCD_TYPE_ILI9341_SERIAL
#define DISPLAY_WIDTH   240
#define DISPLAY_HEIGHT  320
#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y false
#define DISPLAY_SWAP_XY false
#define DISPLAY_INVERT_COLOR    false
#define DISPLAY_RGB_ORDER  LCD_RGB_ELEMENT_ORDER_BGR
#define DISPLAY_OFFSET_X  0
#define DISPLAY_OFFSET_Y  0
#define DISPLAY_BACKLIGHT_OUTPUT_INVERT false
#define DISPLAY_SPI_MODE 0
#endif

// #ifdef CONFIG_LCD_GC9A01_240X240
// #define LCD_TYPE_GC9A01_SERIAL
// #define DISPLAY_WIDTH   240
// #define DISPLAY_HEIGHT  240
// #define DISPLAY_MIRROR_X true
// #define DISPLAY_MIRROR_Y false
// #define DISPLAY_SWAP_XY false
// #define DISPLAY_INVERT_COLOR    true
// #define DISPLAY_RGB_ORDER  LCD_RGB_ELEMENT_ORDER_BGR
// #define DISPLAY_OFFSET_X  0
// #define DISPLAY_OFFSET_Y  0
// #define DISPLAY_BACKLIGHT_OUTPUT_INVERT false
// #define DISPLAY_SPI_MODE 0
// #endif

// #ifdef CONFIG_LCD_CUSTOM
// #define DISPLAY_WIDTH   240
// #define DISPLAY_HEIGHT  320
// #define DISPLAY_MIRROR_X false
// #define DISPLAY_MIRROR_Y false
// #define DISPLAY_SWAP_XY false
// #define DISPLAY_INVERT_COLOR    true
// #define DISPLAY_RGB_ORDER  LCD_RGB_ELEMENT_ORDER_RGB
// #define DISPLAY_OFFSET_X  0
// #define DISPLAY_OFFSET_Y  0
// #define DISPLAY_BACKLIGHT_OUTPUT_INVERT false
// #define DISPLAY_SPI_MODE 0
// #endif

#endif // _BOARD_CONFIG_H_
