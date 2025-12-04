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
