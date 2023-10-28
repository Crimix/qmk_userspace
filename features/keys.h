#pragma once

#include QMK_KEYBOARD_H

#ifdef KEYBOARD_keychron
#    define COMMON_START USER_START
#else
#    define COMMON_START SAFE_RANGE
#endif