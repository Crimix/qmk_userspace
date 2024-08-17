FEATURES_DIR = features
SRC += keys.c
ifeq ($(strip $(CAPS_WORD_ENABLE)), yes)
SRC += caps_word/caps_word.c
endif
SRC += ansi_mode/ansi_mode.c
SRC += shortcuts/shortcuts.c
SRC += special_layer/special_layer.c
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
SRC += rgb_layers/rgb_layers.c
endif

VPATH += $(TOP_DIR)/users/crimix/$(FEATURES_DIR)