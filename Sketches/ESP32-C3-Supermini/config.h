/**
* @file config.h
* @brief User function toggles for conditional compilation and feature-setting
*/

#define TRANSPORT        BLE

#define KEYBOARD_ENABLE   true
#define MEDIA_ENABLE      true
#define STENO_ENABLE      true
#define MOUSE_ENABLE      true
#define DIGITIZER_ENABLE  true
#define GAMEPAD_ENABLE    true
#define SPACEMOUSE_ENABLE false

#define LED_ENABLE        true  
#define LED_PIN           20    // The Tentacle's string of SK6812 MINI E LEDs are using Pin 20 on the ESP32 C3 Super Mini as the Data pin.
#define LED_COUNT         48    // The Tentacle uses a string of 48 NeoPixel LEDs in total.

#define OLED_ENABLE       true  // The OLED connected the Tentacle is 64 pixels tall and 128 pixels wide.
#define OLED_HEIGHT       64
#define OLED_WIDTH        128

#define I2C_ENABLE        true  // The OLED used by the Tentacle relies on I2C, so I2C must be enabled for it to function.
#define SDA_PIN           8
#define SCL_PIN           9
