SRC += crimix.c

VIA_ENABLE = yes
BOOTMAGIC_ENABLE = yes
TAP_DANCE_ENABLE = yes

  SRC += common/features/keys.c
CAPS_WORD_ENABLE    = yes
  SRC += common/features/caps_word/caps_word.c
  SRC += common/features/shortcuts/shortcuts.c