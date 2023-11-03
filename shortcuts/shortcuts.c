#include "shortcuts.h"

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
    }
    return true;
}