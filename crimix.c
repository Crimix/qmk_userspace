#include QMK_KEYBOARD_H

#ifdef CAPS_WORD_ENABLE
    #include "common/features/caps_word/caps_word.h"
#endif // CAPS_WORD_ENABLE

enum layers {
  MAC,
  MAC_FN,
  WIN,
  WIN_FN,
  SPECIAL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    #ifdef CAPS_WORD_ENABLE
    if (!process_record_caps_word(keycode, record)) {
        return false;
    }
    #endif // CAPS_WORD_ENABLE
    switch (keycode) {
    case LT(WIN_FN, KC_F21):
        if (record->tap.count > 0) {
          if (record->event.pressed) {
            set_oneshot_layer(SPECIAL, ONESHOT_OTHER_KEY_PRESSED);
          }
          return false;
      }
      break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case WIN_FN:
        case SPECIAL:
            rgb_matrix_enable_noeeprom();
            break;
        default: // for any other layers, or the default layer
            rgb_matrix_disable_noeeprom();
            break;
    }
  return state;
}

void eeconfig_init_user() {
    rgb_matrix_disable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_WHITE);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == SPECIAL || layer == WIN_FN) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (keycode > KC_TRNS) {
                        if (layer == WIN_FN) {
                            rgb_matrix_set_color(index, RGB_ORANGE);
                        } else if (layer == SPECIAL) {
                            // if (keycode == ) {
                            //     rgb_matrix_set_color(index, RGB_BLUE);
                            // } else {
                            rgb_matrix_set_color(index, RGB_BLUE);
                            // }
                        }
                    }
                }
            }
        }
    }
    return false;
}


