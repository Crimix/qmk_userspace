#pragma once

#include "crimix.h"

#ifdef KEYBOARD_keychron
#    define COMMON_START USER_START
#else
#    define COMMON_START SAFE_RANGE
#endif

enum custom_keycodes {
    KC_CW_NORMAL = COMMON_START,
    KC_CW_COC,
    KC_CW_CAC,
    KC_CW_SNC,
    KC_SC_INTELLIJ_RENAME,
    KC_SC_INTELLIJ_GENERATE,
    SAFE_RANGE_AFTER_COMMON
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);