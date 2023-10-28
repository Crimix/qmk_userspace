SRC += crimix.c
INTROSPECTION_KEYMAP_C = crimix.c

VIA_ENABLE = yes
BOOTMAGIC_ENABLE = yes
TAP_DANCE_ENABLE = yes

CAPS_WORD_ENABLE    = yes
  SRC += common/features/caps_word/caps_word.c
  SRC += common/features/shortcuts/shortcuts.c