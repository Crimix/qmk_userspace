# Caps word
This implementation is based on [Ga68’s multi-mode Caps Word](https://github.com/Ga68/qmk_firmware/blob/my_layout/keyboards/sofle/keymaps/Ga68/caps_word.c)

## Usage
Include it as the following

### <keymap>.c
Include the `caps_word.h` if the CAPS_WORD feature is enabled
```
#ifdef CAPS_WORD_ENABLE
    #include "common/features/caps_word/caps_word.h"
#endif // CAPS_WORD_ENABLE
```

Handle the `CAPS_WORD` key to toggle caps word on using the different modes
```
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef CAPS_WORD_ENABLE
        case CW_TOGG:
            if (record->event.pressed) {
                toggle_caps_word_mode(CAPS_WORD_MODE_DEFAULT);
                return false;
            }
            break;
#endif // CAPS_WORD_ENABLE
    }
    return true;
}
```

### rules.mk
Include the `caps_word.c` and enable CAPS_WORD
```
CAPS_WORD_ENABLE    = yes
 SRC += common/features/caps_word/caps_word.c
```