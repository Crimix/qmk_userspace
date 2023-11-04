#include "shortcuts.h"

// this converts to string
#define STR_(X) #X

// this makes sure the argument is expanded before converting to string
#define STR(X) STR_(X)

bool process_record_shortcuts(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SC_IJ_R:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_F6) SS_UP(X_F6) SS_UP(X_LSFT));
                return false;
            }
            break;
        case SC_IJ_G:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_INS) SS_UP(X_INS) SS_UP(X_LALT));
                return false;
            }
            break;
        case SC_IJ_T:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_DOWN(X_T) SS_UP(X_T) SS_DOWN(X_LSFT) SS_UP(X_LCTL));
                return false;
            }
            break;
        case SC_IJ_P:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LSFT) SS_DOWN(X_K) SS_UP(X_K) SS_DOWN(X_LSFT) SS_UP(X_LCTL));
                return false;
            }
            break;
        case SC_IJ_C:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_K) SS_UP(X_K) SS_UP(X_LCTL));
                return false;
            }
            break;
        case SC_MVH:
            if (record->event.pressed) {
                SEND_STRING("Mvh\n" STR(FIRST_NAME));
                return false;
            }
            break;
    }
    return true;
}