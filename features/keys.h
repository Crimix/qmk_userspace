#ifdef KEYBOARD_keychron
#    define COMMON_START USER_START
#else
#    define COMMON_START SAFE_RANGE
#endif

enum {
    KC_CW_NORMAL = COMMON_START,
    KC_CW_COC,
    KC_CW_CAC,
    KC_CW_SNC,
	SAFE_RANGE_AFTER_COMMON
};