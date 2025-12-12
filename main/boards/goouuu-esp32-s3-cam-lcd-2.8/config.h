/*
    Board pin configuration for Goouuu ESP32-S3-CAM-LCD-2.8-v1.2
    -1. Pin usage summary
    --------------------------------------------------------------------------------------------------------
    Esp32-S3-CAM        Camera          LCDili9341          AUDIO               SD        Other
    --------------------------------------------------------------------------------------------------------
    GPIO_0              X               PIN8_BACKLIGHT/LED  X                   X         BUTTON_BOOT
    GPIO_1              X               X                   I2S_MIC_WS          X         X
    GPIO_2              X               X                   I2S_MIC_SCK         X         X
    GPIO_3              X               PIN7_CLK/SCK        X                   X         X
    GPIO_4              PIN_SIOD        X                   X                   X         X
    GPIO_5              PIN_SIOC        X                   X                   X         X
    GPIO_6              PIN_VSYNC       X                   X                   X         X
    GPIO_7              PIN_HREF        X                   X                   X         X
    GPIO_8              PIN_D2          X                   X                   X         X
    GPIO_9              PIN_D1          X                   X                   X         X
    GPIO_10             PIN_D3          X                   X                   X         X
    GPIO_11             PIN_D0          X                   X                   X         X
    GPIO_12             PIN_D4          X                   X                   X         X
    GPIO_13             PIN_PCLK        X                   X                   X         X
    GPIO_14             X               PIN3_CS             X                   X         X
    GPIO_15             PIN_XCLK        X                   X                   X         X
    GPIO_16             PIN_D7          X                   X                   X         X
    GPIO_17             PIN_D6          X                   X                   X         X
    GPIO_18             PIN_D5          X                   X                   X         X
    GPIO_19             X               X                   X                   X         X
    GPIO_20             X               X                   X                   X         X
    GPIO_21             X               PIN4_RST            X                   X         X
    GPIO_35             X               X                   X                   X         X
    GPIO_36             X               X                   X                   X         X
    GPIO_37             X               X                   X                   X         VOLUME_UP_BUTTON_GPIO
    GPIO_38             X               X                   X                   SD_CMD    VOLUME_DOWN_BUTTON_GPIO
    GPIO_39             X               X                   I2S_SPK_DOUT        SD_CLK    X
    GPIO_40             X               X                   I2S_SPK_BCLK        SD_DATA   X
    GPIO_41             X               X                   I2S_SPK_LRCK        X         X
    GPIO_42             X               X                   I2S_MIC_DIN         X         X
    GPIO_43             X               X                   X                   X         X
    GPIO_44             X               X                   X                   X         X
    GPIO_45             X               PIN6_MOSI/SDI       X                   X         X
    GPIO_46             X               X                   X                   X         X
    GPIO_47             X               PIN5_DC             X                   X         X
    GPIO_48             X               X                   X                   X         BUILTIN_LED
    GPIO_NC             PIN_PWDN        X                   X                   X         X
    GPIO_NC             PIN_RESET       X                   X                   X         X
    GPIO_NC             X               X                   X                   X         BUTTON_TOUCH
    --------------------------------------------------------------------------------------------------------

    -2. Pinout diagram
    --------------------------------------------------------------------------------------------------------
                            Goouuu ESP32-S3-CAM Board Pinout Diagram
                                ━━━━┓    ┏━━━━┓    ┏━━━━━━┳━━━┓
                                    ┗━━━━┛    ┗━━━━┛      ┃   ┃
                         ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━┻━━━━━━━━━━┓
                        ━╋━━ 20 -- 3.3V/VCC_OUT  ||  GPIO43/TXD0 -- 1  ━━╋━                                                                                          
      [BTIN]BUTTON_REST ━╋━━ 19 -- RST           ||  GPIO44/RXD0 -- 2  ━━╋━
      [BTIN]CAMERA_SIOD ━╋━━ 18 -- GPIO 4        ||       GPIO 1 -- 3  ━━╋━ AUDIO_I2S_MIC_GPIO_WS
      [BTIN]CAMERA_SIOC ━╋━━ 17 -- GPIO 5        ||       GPIO 2 -- 4  ━━╋━ AUDIO_I2S_MIC_GPIO_SCK  
     [BTIN]CAMERA_VSYNC ━╋━━ 16 -- GPIO 6        ||       GPIO42 -- 5  ━━╋━ AUDIO_I2S_MIC_GPIO_DIN
      [BTIN]CAMERA_HREF ━╋━━ 15 -- GPIO 7        ||       GPIO41 -- 6  ━━╋━ AUDIO_I2S_SPK_GPIO_LRCK
      [BTIN]CAMERA_XCLK ━╋━━ 14 -- GPIO15        ||       GPIO40 -- 7  ━━╋━ AUDIO_I2S_SPK_GPIO_BCLK/[BTIN]SD_DATA
        [BTIN]CAMERA_D7 ━╋━━ 13 -- GPIO16        ||       GPIO39 -- 8  ━━╋━ AUDIO_I2S_SPK_GPIO_DOUT/[BTIN]SD_CLK
        [BTIN]CAMERA_D6 ━╋━━ 12 -- GPIO17        ||       GPIO38 -- 9  ━━╋━ [BTIN]SD_CMD  
        [BTIN]CAMERA_D5 ━╋━━ 11 -- GPIO18        ||       GPIO37 -- 10 ━━╋━    
        [BTIN]CAMERA_D2 ━╋━━ 10 -- GPIO 8        ||       GPIO36 -- 11 ━━╋━
       DISPLAY_CLK_PIN7 ━╋━━  9 -- GPIO 3        ||       GPIO35 -- 12 ━━╋━ 
                        ━╋━━  8 -- GPIO46        ||       GPIO 0 -- 13 ━━╋━ DISPLAY_BACKLIGHT_PIN8/[BTIN]BUTTON_BOOT
        [BTIN]CAMERA_D1 ━╋━━  7 -- GPIO 9        ||       GPIO45 -- 14 ━━╋━ DISPLAY_MOSI_PIN6
        [BTIN]CAMERA_D3 ━╋━━  6 -- GPIO10        ||       GPIO48 -- 15 ━━╋━ [BTIN]LED
        [BTIN]CAMERA_D0 ━╋━━  5 -- GPIO11        ||       GPIO47 -- 16 ━━╋━ DISPLAY_DC_PIN5
        [BTIN]CAMERA_D4 ━╋━━  4 -- GPIO12        ||       GPIO21 -- 17 ━━╋━ DISPLAY_RST_PIN4
      [BTIN]CAMERA_PCLK ━╋━━  3 -- GPIO13        ||       GPIO20 -- 18 ━━╋━ DISPLAY_CS_PIN6/[BTIN]OTG_DP1
        DISPLAY_CS_PIN3 ━╋━━  2 -- GPIO14        ||       GPIO19 -- 19 ━━╋━ BOOT_BUTTON/[BTIN]OTG_DN1
                        ━╋━━  1 -- 5V/VCC_IN     ||          GND -- 20 ━━╋━
                         ┗━━━━━┳━━━━━━━┳━━━━━━━━━━━━━━━━━━━┳━━━━━━━┳━━━━━┛
                                  OTG                        CH340(USB2UART)
                        
    Note:
      [BTIN] : built-in.
      CAMERA slot: 24 PINS,for OV2640/OV3660/OV5640/OV7725/OV9650 cameras;
      SD slot : 9 PINS,for microSD card;
      Display : 14 PINS,for ILI9341 : 2.8 inch SPI LCD;
                4 pins for OLED 0.96 inch I2C LCD (optional).
      Button : Boot Button on board,connect to GPIO0,for power off ESP32-S3-CAM board.
               Reset Button on board,connect to RST,for reset ESP32-S3-CAM board.
               Touch Button (optional),for user defined.


     ┃ ━ ╋ ┏ ┓ ┗ ┛  ┳ ┻ ┣ ┫ ┳ ┻ 
    --------------------------------------------------------------------------------------------------------
*/

#ifndef _BOARD_CONFIG_H_
#define _BOARD_CONFIG_H_

#include <driver/gpio.h>

/************************ 硬件配置 ************************/
// Audio sample rate
#define AUDIO_INPUT_SAMPLE_RATE 16000
#define AUDIO_OUTPUT_SAMPLE_RATE 24000

// Audio I2S pin configuration
// 如果使用 Duplex I2S 模式，请注释下面一行
#define AUDIO_I2S_METHOD_SIMPLEX
#ifdef AUDIO_I2S_METHOD_SIMPLEX

#define AUDIO_I2S_MIC_GPIO_WS GPIO_NUM_1
#define AUDIO_I2S_MIC_GPIO_SCK GPIO_NUM_2
#define AUDIO_I2S_MIC_GPIO_DIN GPIO_NUM_42
#define AUDIO_I2S_SPK_GPIO_LRCK GPIO_NUM_41
#define AUDIO_I2S_SPK_GPIO_BCLK GPIO_NUM_40
#define AUDIO_I2S_SPK_GPIO_DOUT GPIO_NUM_39

#else

#define AUDIO_I2S_GPIO_WS GPIO_NUM_4
#define AUDIO_I2S_GPIO_BCLK GPIO_NUM_5
#define AUDIO_I2S_GPIO_DIN GPIO_NUM_6
#define AUDIO_I2S_GPIO_DOUT GPIO_NUM_7

#endif

// A MCP Test: Control a lamp
// #define LAMP_GPIO GPIO_NUM_14

// Button Config
#define BUILTIN_LED_GPIO GPIO_NUM_48        // built-in LED
#define BOOT_BUTTON_GPIO GPIO_NUM_0         // boot、唤醒、打断
#define TOUCH_BUTTON_GPIO GPIO_NUM_NC       //
#define VOLUME_UP_BUTTON_GPIO  GPIO_NUM_NC //GPIO_NUM_37  // 音量增//
#define VOLUME_DOWN_BUTTON_GPIO GPIO_NUM_NC // GPIO_NUM_38 // 音量减//

// Camera Config
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
#define DISPLAY_CS_PIN3 GPIO_NUM_14 //
#define DISPLAY_RST_PIN4 GPIO_NUM_21
#define DISPLAY_DC_PIN5 GPIO_NUM_47
#define DISPLAY_MOSI_PIN6 GPIO_NUM_45     //
#define DISPLAY_CLK_PIN7 GPIO_NUM_3       //
#define DISPLAY_BACKLIGHT_PIN8 GPIO_NUM_0 //
#define DISPLAY_MISO_PIN9 GPIO_NUM_NC     // GPIO_NUM_46     //
// #define DISPLAY_SDA_PIN GPIO_NUM_45
// #define DISPLAY_SCL_PIN GPIO_NUM_46

#ifdef LCD_TYPE_ILI9341_TOUCH_PIN
#define DISPLAY_TCLK_PIN10 GPIO_NUM_42 //
#define DISPLAY_TCS_PIN11 GPIO_NUM_1   //
#define DISPLAY_TDIN_PIN12 GPIO_NUM_2  //
#define DISPLAY_TDO_PIN13 GPIO_NUM_41  //
#define DISPLAY_TIRQ_PIN14 GPIO_NUM_NC //
#endif

// OLED 0.96inch I2C PIN Config
#ifdef CONFIG_GOOUUU_ESP32_S3_CAM_V1_2_LCD_OLED_0_96_I2C
#define DISPLAY_SCL_PIN3 GPIO_NUM_41
#define DISPLAY_SDA_PIN4 GPIO_NUM_42
#endif

#ifdef CONFIG_GOOUUU_ESP32_S3_CAM_V1_2_LCD_ILI9341_NO_IPS
#define LCD_TYPE_ILI9341_SERIAL
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320
#define DISPLAY_MIRROR_X true
#define DISPLAY_MIRROR_Y false
#define DISPLAY_SWAP_XY false
#define DISPLAY_INVERT_COLOR false
#define DISPLAY_RGB_ORDER LCD_RGB_ELEMENT_ORDER_BGR
#define DISPLAY_OFFSET_X 0
#define DISPLAY_OFFSET_Y 0
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
