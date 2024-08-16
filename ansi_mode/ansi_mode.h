#pragma once

#include "keys.h"

typedef enum {
    ANSI_MODE_OFF = 0,
    ANSI_MODE_ON
} ansi_mode_state_t;

#define ANSI_MODE_STATE_DEFAULT ANSI_MODE_OFF

ansi_mode_state_t g_ansi_mode_state;

void toggle_ansi_mode(ansi_mode_state_t state);
bool process_record_ansi_mode(uint16_t keycode, keyrecord_t *record);