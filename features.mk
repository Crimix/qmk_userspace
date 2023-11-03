FEATURES_DIR = features
    ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
        SRC += $(FEATURES_DIR)/caps_word/caps_word.c
    endif
SRC += $(features)/shortcuts/shortcuts.c

VPATH += $(TOP_DIR)/users/crimix/$(COMMON_DIR)