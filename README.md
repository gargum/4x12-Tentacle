# Tentacle

![Tentacle](https://raw.githubusercontent.com/gargum/4x12-Tentacle/refs/heads/main/pic/Tentacle_Board.jpg "This is the world's first SquidHID device!")

The **Tentacle** is the first device to use the SquidHID firmware! It is a 4x12 keyboard utilising a Japanese duplex matrix.

## Features

 - [x] Simultaneous Choc and MX switch support
 - [x] Per-key LEDs
 - [x] 128x64 OLED screen
 - [x] Rechargeable battery system based around the TP4056
 - [x] Designed for testing SquidHID functionality on all versions of the ESP32 Super Mini, and all versions of the Xiao Seeed

 ## Firmware

 This keyboard uses SquidHID, which is an Arduino IDE library at the time of writing.

 To flash this on your keyboard, first make sure your installation of Arduino IDE has the **NimBLE-Arduino** library installed.

 Afterwards, simply download the SquidHID repository as a .ZIP file, and extract it into the **Arduino/libraries/** directory where NimBLE-Arduino is also stored.

 Next, for the ESP32 C3 Super Mini, modify the included config.h file as follows:

 ``` C++
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
#define SPACEMOUSE_ENABLE false  // Please note that if the Spacemouse is turned on, the Mouse, Digitizer and Gamepad must be turned off. 

#define LED_ENABLE        true  
#define LED_PIN           20    // The Tentacle's string of SK6812 MINI E LEDs are using Pin 20 on the ESP32 C3 Super Mini as the Data pin.
#define LED_COUNT         48    // The Tentacle uses a string of 48 NeoPixel LEDs in total.

#define OLED_ENABLE       true  // The OLED connected the Tentacle is 64 pixels tall and 128 pixels wide.
#define OLED_HEIGHT       64
#define OLED_WIDTH        128

#define I2C_ENABLE        true  // The OLED used by the Tentacle relies on I2C, so I2C must be enabled for it to function.
#define SDA_PIN           8
#define SCL_PIN           9
 ```

 At this point, you should be able to use this sketch to flash your keyboard:

 ``` C++
/**
 * @file Tentacle.ino
 * @brief Main sketch for the Tentacle 4x12 keyboard
 */

#include <SQUIDHID.h>

SQUIDHID esp("SquidHID", "SquidHID", 100);

MATRIX(matrix) = { 
      {1, 3}, {1, 7}, {2, 4}, {3, 1}, {3, 7}, {4, 3}, {5, 1}, {5, 7}, {6, 4}, {7, 1}, {7, 5}, {10,4}, 
      {1, 4}, {1,10}, {2, 5}, {3, 2}, {3,10}, {4, 6}, {5, 2}, {5,10}, {6, 5}, {7, 2}, {7, 6}, {10,5}, 
      {1, 5}, {2, 1}, {2, 6}, {3, 5}, {4, 1}, {4, 7}, {5, 3}, {6, 1}, {6, 7}, {7, 3}, {10,2}, {10,6}, 
      {1, 6}, {2, 3}, {2,10}, {3, 6}, {4, 2}, {4,10}, {5, 4}, {6, 2}, {6,10}, {7, 4}, {10,3}, {10,7} 
};

LAYER(base_layer) = {    
       KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS, 
       KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,    KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, 
       KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, 
       MO(1),   KC_LGUI, KC_MINS, KC_PGDN, KC_SPC, KC_BSPC, KC_ENT, KC_LSFT, KC_PGUP, KC_EQL, KC_RGUI, MO(2)
};

LAYER(function_layer) = {
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10, KC_F11,  KC_F12, 
       KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,    KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_QUOT, 
       KC_LCTL, KC_VOLD, KC_MPRV, KC_MRWD, KC_MSTP,KC_WBAK, KC_WFWD,KC_MPLY, KC_MFFD, KC_MNXT,KC_VOLU, KC_RCTL, 
       TRANS,   KC_PGDN, KC_DOWN, KC_LEFT, KC_SPC, KC_BSPC, KC_ENT, KC_LSFT, KC_RGHT, KC_UP,  KC_PGUP, TRANS
};

KEYMAP(layers) = {
    base_layer,
    function_layer, 
};

void setup() {
  esp.setLogLevel(LOGGER_VERBOSE);
  esp.setAppearance(KEYBOARD);
  
  esp.begin(matrix, layers);  
  
  esp.initializeLEDs(LED_COUNT, LED_PIN, NEO_GRB);
  esp.setLEDBrightness(50);
  esp.fillLEDs(RGB_AZURE);

  esp.oledClear();
  esp.oledDrawBitmap_P(0, 0, 64, 64, real_squid, OLED::WHITE);
  esp.oledDrawString(64, 24, "SquidHID", OLED::NORMAL_SIZE, OLED::WHITE);
  esp.oledDisplayUpdate();
}

void loop() {  

  esp.update();

}
 ```

## Power Circuit

The Tentacle uses a TP4056 alongside 3x2N7002 transistors, a 10k resistor, and an SPDT to toggle between charging and discharging.

The common pin on the SPDT switch is connected to the 5V/VIN pin on the microcontroller. The two other pins are connected to I+ and O+ respectively on the TP4056 module.

When I+ and 5V are connected via the switch, I+ triggers two transistors. The first on connects I- the GND on the microcontroller, while the second transistor connects a pull-up to GND, which in turn prevents O- from being connected to GND.

When O+ and 5V are connected via the switch, the pull-up is able to do its job, which is to trigger the third transistor, allowing O- to connect to GND.

With this arrangement, one switch toggles between two more complex states - O+ to 5V + O- to GND, and I+ to 5V + I- to GND. This ensures both convenience, and safety.

Below is a crude diagram of the wiring for this setup:

![TP4056 Power Circuit](https://raw.githubusercontent.com/gargum/4x12-Tentacle/refs/heads/main/pic/Power_Schematic.jpg "In complete seriousness, yes, yes I do do all my schematics on literal paper. Fight me")
