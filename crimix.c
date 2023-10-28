#include QMK_KEYBOARD_H

#ifdef CAPS_WORD_ENABLE
    #include "common/features/caps_word/caps_word.h"
#endif // CAPS_WORD_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CAPS_WORD_ENABLE
    if (!process_record_caps_word(keycode, record)) {
        return false;
    }
    #endif // CAPS_WORD_ENABLE
    switch (keycode) {
    case LT(3, KC_F21):
        if (record->tap.count > 0) {
          if (record->event.pressed) {
            if (IS_LAYER_ON(4)) {
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            } else {
                set_oneshot_layer(4, ONESHOT_START);
            }
          }
          return false;
      }
      break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 4:
            rgb_matrix_enable();
            break;
        default: // for any other layers, or the default layer
            rgb_matrix_disable();
            rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
  return state;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == 4 || layer == 3) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (keycode > KC_TRNS) {
                        if (layer == 3) {
                            rgb_matrix_set_color(index, RGB_ORANGE);
                        } else if (layer == 4) {
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


