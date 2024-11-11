#include "board.h"
#include <stdlib.h>

void buttons_init(void) {
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = BTN_MENU_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(BTN_MENU_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = BTN_ENTER_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(BTN_ENTER_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = BTN_NEXT_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(BTN_NEXT_PORT, &GPIO_InitStructure);   
}
