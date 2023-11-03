#include "shortcuts.h"
#include "keymap.h"


bool process_record_shortcuts(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SC_INTELLIJ_RENAME:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LSFT) SS_TAP(X_F6));
                return false;
            }
            break;
        case KC_SC_INTELLIJ_GENERATE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LALT) SS_TAP(X_INS));
                return false;
            }
            break;
    }
    return true;
}