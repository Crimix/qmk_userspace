#include QMK_KEYBOARD_H

#ifdef CAPS_WORD_ENABLE
    #include "common/features/caps_word.h"
#endif // CAPS_WORD_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_leader(keycode, record)) { return false; }

    switch (keycode) {
        case CAPS_WORD:
            if (record->event.pressed) {
                toggle_caps_word_mode(CAPS_WORD_MODE_DEFAULT);
                return false;
            }
            break;
    }
    return true;
}