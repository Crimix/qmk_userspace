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

enum {
    TD_SPEC = 0 
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(SPECIAL, ONESHOT_OTHER_KEY_PRESSED);
            break;
        case TD_SINGLE_HOLD:
            layer_on(WIN_FN);
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(WIN_FN);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TD_SPEC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CAPS_WORD_ENABLE
    if (!process_record_caps_word(keycode, record)) {
        return false;
    }
    #endif // CAPS_WORD_ENABLE
    switch (keycode) {
   
    }
    return true;
}

void eeconfig_init_user() {
    rgb_matrix_disable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_WHITE);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == SPECIAL || layer == WIN_FN) {
        rgb_matrix_enable_noeeprom();
        rgb_matrix_set_color_all(RGB_OFF);
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
    } else {
        rgb_matrix_reload_from_eeprom();
    }
    return false;
}


