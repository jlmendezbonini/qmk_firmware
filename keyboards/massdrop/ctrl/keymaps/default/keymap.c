#include QMK_KEYBOARD_H

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F14,  KC_F15,  LCTL(KC_UP), KC_F11,   LALT(LCMD(KC_ESC)),   DM_REC1, DM_PLY1, KC_MPRV, KC_MPLY, KC_MNXT,  KC_VOLD,   KC_VOLU,             _______,              _______,              TO(1), \
        KC_GRV,  KC_1,    KC_2,    KC_3,        KC_4,     KC_5,                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,   KC_EQL,  KC_BSPC,    LCTL(LCMD(KC_J)),     KC_F6,                LCTL(LALT(LCMD(KC_SPC))), \
        KC_TAB,  KC_Q,    KC_W,    KC_E,        KC_R,     KC_T,                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,   KC_RBRC, KC_BSLS,    KC_DEL,               LCMD(LSFT(KC_LBRC)),  LCMD(LSFT(KC_RBRC)), \
        KC_CAPS, KC_A,    KC_S,    KC_D,        KC_F,     KC_G,                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,   KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,        KC_V,     KC_B,                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LALT, KC_LCMD,                           KC_SPC,                        KC_RCMD, KC_RALT, KC_NO,    KC_RCTL,                 KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, _______, TO(0), \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
}

void keyboard_post_init_user(void) {
    // rgb_matrix_set_color(41, 255, 0, 0);
}
//       ESC                                                                                                          
//     ___0___, _______, _______, _______, ___4___, _______, _______, _______, _______, ___9__, _______, _______,  ___12__,           _______, _______, __15___, 
//     ___16__, _______, __18___, _______, _______, _______, _______, __23___, _______, ______, _______, __27___,  _______, _______,  ___30__, _______, __32___, 
//     __ 33__, _______, __35___, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  ___47___, _______, _______, 
//     ___50__, _______,________, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___62__, 
//     ___63__, _______, _______, _______, _______, _______, _______, ___70__, _______, _______, _______, ___74__,                              ___75___, 
//     ___76___, _______, _______,                   ___79___,                           _______, _______, _______, _______,            ______, ___85___, _______ 
void rgb_matrix_indicators_kb(void) {
    // 	if (!g_suspend_state && rgb_matrix_config.enable) {
    //     switch (get_highest_layer(layer_state)) {
    //         case 0:
    //             rgb_matrix_set_color_all(RGB_BLACK);
    //             rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    //             break;
    //         case 1:
    //             rgb_matrix_set_color_all(RGB_BLACK);
    //             rgb_matrix_set_color(75, RGB_BLUE);
    //             rgb_matrix_set_color(85, RGB_YELLOW);
    //             break;
    //     }
    // }

    #ifdef USB_LED_INDICATOR_ENABLE
      md_rgb_matrix_indicators();
    #endif // USB_LED_INDICATOR_ENABLE

}


#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

