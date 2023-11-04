#include "crimix.h"
#include "sendstring_danish.h"

bool disable_rgb_layers = false;

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BAT_LVL:
            if (record->event.pressed) {
                disable_rgb_layers = true;
            } else {
                disable_rgb_layers = false;
            }
            break;
    }

    return true;
}

bool pre_rgb_layer_highlight(uint8_t led_min, uint8_t led_max) {
    return disable_rgb_layers;
}

void set_custom_indicator(uint8_t index) {
    rgb_matrix_set_color(index, RGB_RED);
}