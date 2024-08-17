#include "rgb_layers.h"
#include "../special_layer/special_layer.h"
#include "../ansi_mode/ansi_mode.h"

#ifdef LED_MATRIX_ENABLE
#    define SET_ALL_LED_OFF() led_matrix_set_value_all(0)
#    define SET_LED_OFF(idx) led_matrix_set_value(idx, 0)
#    define SET_LED_ON(idx) led_matrix_set_value(idx, 255)
#    define LED_DRIVER_DISABLE_TIME_RESET led_matrix_disable_time_reset
#endif

#ifdef RGB_MATRIX_ENABLE
#    define SET_ALL_LED_OFF() rgb_matrix_set_color_all(0, 0, 0)
#    define SET_LED_OFF(idx) rgb_matrix_set_color(idx, 0, 0, 0)
#    define SET_LED_ON(idx) rgb_matrix_set_color(idx, 255, 255, 255)
#endif

bool is_layer_rendering = false;

__attribute__((weak)) 
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);
    if (layer == COMMON_SPECIAL || layer == COMMON_WIN_FN) {
        is_layer_rendering = true;
        rgb_matrix_enable_noeeprom();
    } else {
        is_layer_rendering = false;
        rgb_matrix_reload_from_eeprom();
    }
    return layer_state_set_keymap(state);
}


__attribute__((weak)) 
bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return false;
}

__attribute__((weak)) 
bool pre_rgb_layer_highlight(uint8_t led_min, uint8_t led_max) {
    return false;
}

__attribute__((weak)) 
void set_custom_indicator(uint8_t index) {
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if(!pre_rgb_layer_highlight(led_min, led_max)) {
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
    }

    if(!is_layer_rendering) {
#if defined(CAPS_LOCK_INDEX)
        if (host_keyboard_led_state().caps_lock) {
            set_custom_indicator(CAPS_LOCK_INDEX);
        }
#endif
#if defined(NUM_LOCK_INDEX)
        if (host_keyboard_led_state().num_lock) {
            set_custom_indicator(NUM_LOCK_INDEX);
        }
#endif
#if defined(SCROLL_LOCK_INDEX)
        if (host_keyboard_led_state().scroll_lock) {
            set_custom_indicator(SCROLL_LOCK_INDEX);
        }
#endif
#if defined(COMPOSE_LOCK_INDEX)
        if (host_keyboard_led_state().compose) {
            set_custom_indicator(COMPOSE_LOCK_INDEX);
        }
#endif
#if defined(KANA_LOCK_INDEX)
        if (host_keyboard_led_state().kana) {
            set_custom_indicator(KANA_LOCK_INDEX);
        }
#endif
#if defined(ANSI_MODE_INDEX)
        if (is_ansi_mode()) {
            set_custom_indicator(ANSI_MODE_INDEX);
        }
#endif
    }

    return rgb_matrix_indicators_advanced_keymap(led_min, led_max);
}

__attribute__((weak)) 
bool led_update_keymap(led_t led_state) {
    return true;
}

#if !defined(KC_BLUETOOTH_ENABLE) && !defined(LK_WIRELESS_ENABLE)
bool led_update_user(led_t led_state) {
#if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        SET_LED_ON(CAPS_LOCK_INDEX);
    } else {
        SET_LED_OFF(CAPS_LOCK_INDEX);
    }
#endif
#if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock) {
        SET_LED_ON(NUM_LOCK_INDEX);
    } else {
        SET_LED_OFF(NUM_LOCK_INDEX);
    }
#endif
#if defined(SCROLL_LOCK_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        SET_LED_ON(SCROLL_LOCK_INDEX);
    } else {
        SET_LED_OFF(SCROLL_LOCK_INDEX);
    }
#endif
#if defined(COMPOSE_LOCK_INDEX)
    if (host_keyboard_led_state().compose) {
        SET_LED_ON(COMPOSE_LOCK_INDEX);
    } else {
        SET_LED_OFF(COMPOSE_LOCK_INDEX);
    }
#endif
#if defined(KANA_LOCK_INDEX)
    if (host_keyboard_led_state().kana) {
        SET_LED_ON(KANA_LOCK_INDEX);
    } else {
        SET_LED_OFF(KANA_LOCK_INDEX);
    }
#endif
#if defined(ANSI_MODE_INDEX)
    if (is_ansi_mode()) {
        SET_LED_ON(ANSI_MODE_INDEX);
    } else {
        SET_LED_OFF(ANSI_MODE_INDEX);
    }
#endif

    return led_update_keymap(led_state);
}

#else

void os_state_indicate(void) {
#if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock) {
#if defined(DIM_CAPS_LOCK)
        SET_LED_OFF(CAPS_LOCK_INDEX);
#else
        SET_LED_ON(CAPS_LOCK_INDEX);
#endif
    }
#endif
#if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock) {
        SET_LED_ON(NUM_LOCK_INDEX);
    }
#endif
#if defined(SCROLL_LOCK_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        SET_LED_ON(SCROLL_LOCK_INDEX);
    }
#endif
#if defined(COMPOSE_LOCK_INDEX)
    if (host_keyboard_led_state().compose) {
        SET_LED_ON(COMPOSE_LOCK_INDEX);
    }
#endif
#if defined(KANA_LOCK_INDEX)
    if (host_keyboard_led_state().kana) {
        SET_LED_ON(KANA_LOCK_INDEX);
    }
#endif
#if defined(ANSI_MODE_INDEX)
    if (is_ansi_mode()) {
        SET_LED_ON(ANSI_MODE_INDEX);
    }
#endif
}
#endif