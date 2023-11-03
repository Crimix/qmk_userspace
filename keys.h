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
    SC_IJ_R, //IntellIJ Rename
    SC_IJ_G, //IntellIJ Generate
    SC_IJ_T, //IntellIJ Go to test
    SC_IJ_P, //IntellIJ Git push
    SC_IJ_C, //IntellIJ Git commit
    SC_MVH,  //Mvh
    SAFE_RANGE_AFTER_COMMON
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

bool is_intellij_key(uint16_t keycode);