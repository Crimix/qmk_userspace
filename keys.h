#pragma once

#include "crimix.h"
#include "keymap.h"

#ifdef KEYBOARD_keychron
#    define COMMON_START NEW_SAFE_RANGE
#else
#    define COMMON_START SAFE_RANGE
#endif

enum custom_keycodes {
    RGB_STOG = COMMON_START,
    CW_NORMAL,
    CW_COC,
    CW_CAC,
    CW_SNC,
    SC_IJ_R,
    SC_IJ_G,
    SAFE_RANGE_AFTER_COMMON
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

bool is_intellij_key(uint16_t keycode);