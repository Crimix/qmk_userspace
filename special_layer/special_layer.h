#pragma once

#include "config.h"
#include "keys.h"

enum custom_layers {
    COMMON_WIN_FN = LAYER_START,
    COMMON_SPECIAL
};

enum tap_dances {
    TD_SL = 0
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;