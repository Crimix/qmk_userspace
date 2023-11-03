FEATURES_DIR = features
SRC += keys.c
    ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
        SRC += caps_word/caps_word.c
    endif
SRC += shortcuts/shortcuts.c
SRC += special_layer/special_layer.c
SRC += rgb_layers/rgb_layers.c

VPATH += $(TOP_DIR)/users/crimix/$(FEATURES_DIR)