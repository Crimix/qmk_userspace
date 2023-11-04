#include "crimix.h"
#include "sendstring_danish.h"
#include "print.h"

void eeconfig_init_user(void) {
    print("Set EECONFIG")
    rgb_matrix_disable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_WHITE);
}
