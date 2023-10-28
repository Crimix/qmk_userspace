#pragma once

#include QMK_KEYBOARD_H

#ifdef KEYBOARD_keychron
#    define COMMON_START USER_START
#else
#    define COMMON_START SAFE_RANGE
#endif

// clang-format off
enum custom_keycodes {
    KC_CW_NORMAL = COMMON_START,
    KC_CW_COC,
    KC_CW_CAC,
    KC_CW_SNC,
    KC_SC_INTELLIJ_RENAME,
    KC_SC_INTELLIJ_GENERATE,
    SAFE_RANGE_AFTER_COMMON
};