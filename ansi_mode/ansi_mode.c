#include "ansi_mode.h"

ansi_mode_state_t g_ansi_mode_state = ANSI_MODE_STATE_DEFAULT;
bool is_processing = false;

bool is_shift(void) {
    return get_mods() & MOD_MASK_SHIFT;
}

bool is_alt_gr(void) {
    return get_mods() & MOD_MASK_CA;
}

bool is_normal(void) {
    return get_mods() == 0;
}

void process_keycode(uint16_t code) {
    is_processing = true;
    uint8_t current_mods = get_mods();
    clear_keyboard();

    register_code16(code);
    unregister_code16(code);

    set_mods(current_mods);
    is_processing = false;
}

bool ansi_mode_press_user(uint16_t keycode) {
    if (is_processing) {
        return true;
    }

    switch(g_ansi_mode_state) {
        case ANSI_MODE_ON:
            switch (keycode) {
                case KC_NUBS:
                    if (is_shift()) {
                        process_keycode(S(KC_DOT)); //Send >
                        return false;
                    } else if (is_normal()) {
                        process_keycode(S(KC_COMM)); //Send <
                        return false;
                    }
                    return true;
                case KC_COMM:
                    if (is_shift()) {
                        process_keycode(KC_SCLN); //Send ;
                        return false;
                    }
                    return true;
                case KC_DOT:
                    if (is_shift()) {
                        process_keycode(S(KC_SCLN)); //Send :
                        return false;
                    }
                    return true;
                case KC_SLSH:
                    if (is_shift()) {
                        process_keycode(S(KC_MINS)); //Send _
                        return false;
                    } else if (is_normal()) {
                        process_keycode(KC_MINS); //Send -
                        return false;
                    }
                    return true;
                case KC_2:
                    if (is_shift()) {
                        process_keycode(S(KC_QUOT)); //Send "
                        return false;
                    } else if (is_alt_gr()) {
                        process_keycode(S(KC_2)); //Send @
                        return false;
                    }
                    return true;
                case KC_4:
                    if (is_alt_gr()) {
                        process_keycode(S(KC_4)); //Send $
                        return false;
                    }
                    return true;
                case KC_6:
                    if (is_shift()) {
                        process_keycode(S(KC_7)); //Send &
                        return false;
                    }
                    return true;
                case KC_7:
                    if (is_shift()) {
                        process_keycode(KC_SLSH); //Send /
                        return false;
                    } else if (is_alt_gr()) {
                        process_keycode(S(KC_LBRC)); //Send {
                        return false;
                    }
                    return true;
                case KC_8:
                    if (is_shift()) {
                        process_keycode(S(KC_9)); //Send (
                        return false;
                    } else if (is_alt_gr()) {
                        process_keycode(KC_LBRC); //Send [
                        return false;
                    }
                    return true;
                case KC_9:
                    if (is_shift()) {
                        process_keycode(S(KC_0)); //Send )
                        return false;
                    } else if (is_alt_gr()) {
                        process_keycode(KC_RBRC); //Send ]
                        return false;
                    }
                    return true;
                case KC_0:
                    if (is_shift()) {
                        process_keycode(KC_EQL); //Send =
                        return false;
                    } else if (is_alt_gr()) {
                        process_keycode(S(KC_RBRC)); //Send }
                        return false;
                    }
                    return true;
                case KC_MINS:
                    if (is_shift()) {
                        process_keycode(S(KC_SLSH)); //Send ?
                        return false;
                    } else if (is_normal()) {
                        process_keycode(S(KC_EQL)); //Send +
                        return false;
                    }
                    return true;
                case KC_EQL:
                    if (is_shift()) {
                        process_keycode(KC_GRV); //Send `
                        return false;
                    } else if (is_alt_gr()) {
                        process_keycode(S(KC_BSLS)); //Send |
                        return false;
                    }
                    return true;
                case KC_RBRC:
                    if (is_shift()) {
                        process_keycode(S(KC_6)); //Send ^
                        return false;
                    } else if (is_alt_gr()) {
                        process_keycode(S(KC_GRV)); //Send ~
                        return false;
                    }
                    return true;
                case KC_NUHS:
                    if (is_shift()) {
                        process_keycode(KC_8); //Send *
                        return false;
                    } else if (is_normal()) {
                        process_keycode(KC_QUOT); //Send '
                        return false;
                    }
                    return true;

                default:
                    return true;
            }
        
        default:
            return true;
    }
}

bool is_ansi_mode(void) {
    return g_ansi_mode_state == ANSI_MODE_ON;
}

void toggle_ansi_mode(ansi_mode_state_t new_mode) {
    g_ansi_mode_state = new_mode;
}

ansi_mode_state_t get_new_mode(ansi_mode_state_t old_mode) {
    if (old_mode == ANSI_MODE_OFF) {
        return ANSI_MODE_ON;
    } else {
        return ANSI_MODE_OFF;
    }
}

bool process_record_ansi_mode(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SC_ANSI:
            if (record->event.pressed) {
                toggle_ansi_mode(get_new_mode(g_ansi_mode_state));
                return false;
            }
            break;
    }

    if (record->event.pressed) {
        return ansi_mode_press_user(keycode);
    } else {
        return true;
    }
}