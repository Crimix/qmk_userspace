# Crimix's shortcuts

## Usage
First follow the [General readme]{https://github.com/Crimix/qmk_userspace/tree/common/features/readme.md}
Then include it as the following:

### keymap.c
Include the `shortcuts.h`
```
#include "common/features/shortcuts/shortcuts.h"
```
Include which ever keyboard layout you are using
```
#include "sendstring_danish.h"
```

Include the following to handle the different shortcuts
```
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_shortcuts(keycode, record)) {
        return false;
    }
    return true;
}
```

### rules.mk
Include the `shortcuts.c`
```
 SRC += common/features/shortcuts/shortcuts.c
```
