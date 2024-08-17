#include "led_indicators.h"
#include "../ansi_mode/ansi_mode.h"

__attribute__((weak)) 
bool led_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return false;
}

bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#if defined(CAPS_LOCK_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        led_matrix_set_value(CAPS_LOCK_INDEX, 255);
    }
#endif
#if defined(NUM_LOCK_INDEX)
    if (host_keyboard_led_state().num_lock) {
        led_matrix_set_value(NUM_LOCK_INDEX, 255);
    }
#endif
#if defined(SCROLL_LOCK_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        led_matrix_set_value(SCROLL_LOCK_INDEX, 255);
    }
#endif
#if defined(COMPOSE_LOCK_INDEX)
    if (host_keyboard_led_state().compose) {
        led_matrix_set_value(COMPOSE_LOCK_INDEX, 255);
    }
#endif
#if defined(KANA_LOCK_INDEX)
    if (host_keyboard_led_state().kana) {
        led_matrix_set_value(KANA_LOCK_INDEX, 255);
    }
#endif
#if defined(ANSI_MODE_INDEX)
    if (is_ansi_mode()) {
        led_matrix_set_value(ANSI_MODE_INDEX, 255);
    }
#endif

    return led_matrix_indicators_advanced_keymap(led_min, led_max);
}