#include "rgb_layers.h"
#include "../special_layer/special_layer.h"

__attribute__((weak)) 
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    if (layer == COMMON_SPECIAL || layer == COMMON_WIN_FN) {
        rgb_matrix_enable_noeeprom();
    } else {
        rgb_matrix_reload_from_eeprom();
    }
    return layer_state_set_keymap(state);
}


__attribute__((weak)) 
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return false;
}

bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == COMMON_SPECIAL || layer == COMMON_WIN_FN) {
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED) {
                    uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    if (keycode > KC_TRNS) {
                        if (layer == COMMON_WIN_FN) {
                            rgb_matrix_set_color(index, RGB_ORANGE);
                        } else if (layer == COMMON_SPECIAL) {
                            if (is_intellij_key(keycode)) {
                                rgb_matrix_set_color(index, RGB_PURPLE);
                            } else {
                                rgb_matrix_set_color(index, RGB_BLUE);
                            }
                        }
                    } else {
                        rgb_matrix_set_color(index, RGB_OFF);
                    }
                }
            }
        }
    }
    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}