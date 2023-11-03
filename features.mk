FEATURES_DIR = features
    ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
        SRC += caps_word/caps_word.c
    endif
SRC += shortcuts/shortcuts.c

VPATH += $(TOP_DIR)/users/crimix/$(FEATURES_DIR)