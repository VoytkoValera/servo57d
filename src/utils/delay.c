#include <stdint.h>

#include "delay.h"

/**
 * @brief  Inserts a delay time.
 * @param count specifies the delay time length.
 */
void delay(uint32_t count)
{
    volatile uint32_t c = count;
    for (; c > 0; c--)
        ;
}