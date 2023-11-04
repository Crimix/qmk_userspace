#include "keys.h"

#ifdef CAPS_WORD_ENABLE
    #include "caps_word/caps_word.h"
#endif // CAPS_WORD_ENABLE
#include "shortcuts/shortcuts.h"


__attribute__((weak)) 
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_shortcuts(keycode, record)) {
        return false;
    }
    #ifdef CAPS_WORD_ENABLE
    if (!process_record_caps_word(keycode, record)) {
        return false;
    }
    #endif // CAPS_WORD_ENABLE
    switch (keycode) {
    }
  return process_record_keymap(keycode, record);
}

bool is_intellij_key(uint16_t keycode) {
    switch (keycode) {
        case SC_IJ_R:
        case SC_IJ_G:
        case SC_IJ_T:
        case SC_IJ_P:
        case SC_IJ_C:
        return true;
    }
    return false;
}