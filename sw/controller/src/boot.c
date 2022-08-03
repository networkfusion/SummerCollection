#include <stdint.h>
#include <stm32g030xx.h>
#include "hw.h"


void no_valid_image (void) {
    hw_gpio_set(GPIO_ID_LED);
}

void set_vector_table_offset (uint32_t offset) {
    SCB->VTOR = (__IOM uint32_t) (offset);
}