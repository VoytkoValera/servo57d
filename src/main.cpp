#include <stdarg.h>
#include "board.h"
#include <stdint.h>
#include "SEGGER_RTT.h"
#include "fw_version.h"

#include "log.h"
#include "delay.h"




int main(void)
{
    SEGGER_RTT_Init();
    print_log("MKS Servo57d v.%s\n", FW_VERSION);
    board_init();
    LedOn(); /*Turn on Led1*/
    oled_init();

    while (1)
    {       
        /* Insert delay */
        delay(0x28FFFF);
        uint16_t sample = mt6816_read();
        float angle = (360.0 / 16384.0) * sample;
        oled_write((uint16_t)angle);
    }
}
