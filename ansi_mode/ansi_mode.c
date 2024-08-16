#include "ansi_mode.h"

ansi_mode_state_t g_ansi_mode_state = ANSI_MODE_STATE_DEFAULT;
bool is_processing = false;

bool is_shift(void) {
    return get_mods() == MOD_MASK_SHIFT;
}

bool is_alt_gr(void) {
    return get_mods() == MOD_MASK_CA;
}

bool is_normal(void) {
    return get_mods() == 0;
}

bool process_send_string(const char *string) {
    is_processing = true;
    SEND_STRING(string);
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
                        process_send_string(SS_TAP(X_DOT));
                        return false;
                    } else if (is_normal()) {
                        process_send_string(SS_DOWN(X_LSFT) SS_TAP(X_COMM) SS_UP(X_LSFT));
                        return false;
                    }
                    return true;
                case KC_COMM:
                    if (is_shift()) {
                        process_send_string(";");
                        return false;
                    }
                    return true;
                case KC_DOT:
                    if (is_shift()) {
                        process_send_string(":");
                        return false;
                    }
                    return true;
                case KC_SLSH:
                    if (is_shift()) {
                        process_send_string("_");
                        return false;
                    } else if (is_normal()) {
                        process_send_string("-");
                        return false;
                    }
                    return true;
                case KC_2:
                    if (is_shift()) {
                        process_send_string("\"");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("@");
                        return false;
                    }
                    return true;
                case KC_3:
                    if (is_shift()) {
                        process_send_string("#");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("£");
                        return false;
                    }
                    return true;
                case KC_4:
                    if (is_shift()) {
                        process_send_string("¤");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("$");
                        return false;
                    }
                    return true;
                case KC_6:
                    if (is_shift()) {
                        process_send_string("&");
                        return false;
                    }
                    return true;
                case KC_7:
                    if (is_shift()) {
                        process_send_string("/");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("{");
                        return false;
                    }
                    return true;
                case KC_8:
                    if (is_shift()) {
                        process_send_string("(");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("[");
                        return false;
                    }
                    return true;
                case KC_9:
                    if (is_shift()) {
                        process_send_string(")");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("]");
                        return false;
                    }
                    return true;
                case KC_0:
                    if (is_shift()) {
                        process_send_string("=");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("}");
                        return false;
                    }
                    return true;
                case KC_MINS:
                    if (is_shift()) {
                        process_send_string("?");
                        return false;
                    } else if (is_normal()) {
                        process_send_string("+");
                        return false;
                    }
                    return true;
                case KC_EQL:
                    if (is_shift()) {
                        process_send_string("`");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("|");
                        return false;
                    } else if (is_normal()) {
                        process_send_string("´");
                        return false;
                    }
                    return true;
                case KC_RBRC:
                    if (is_shift()) {
                        process_send_string("^");
                        return false;
                    } else if (is_alt_gr()) {
                        process_send_string("~");
                        return false;
                    } else if (is_normal()) {
                        process_send_string("¨");
                        return false;
                    }
                    return true;
                case KC_NUHS:
                    if (is_shift()) {
                        process_send_string("*");
                        return false;
                    } else if (is_normal()) {
                        process_send_string("¨");
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

    return ansi_mode_press_user(keycode);
}