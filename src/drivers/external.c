#include "board.h"
#include <stdlib.h>

void external_init(void) {
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = EXT_DIR_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(EXT_DIR_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = EXT_STEP_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(EXT_STEP_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = EXT_EN_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(EXT_EN_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = EXT_IN1_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(EXT_IN1_PORT, &GPIO_InitStructure);

#ifdef SERVO57D

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = EXT_IN2_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(EXT_IN2_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = EXT_OUT1_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_OD;
    GPIO_InitPeripheral(EXT_OUT1_PORT, &GPIO_InitStructure); 

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = EXT_OUT2_PIN;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_OD;
    GPIO_InitPeripheral(EXT_OUT2_PORT, &GPIO_InitStructure); 


#endif

      
}

void ext_set(uint16_t pin, uint8_t val) {
    if (val)
        EXT3_PORT->PBC = pin;
    else
        EXT3_PORT->PBSC = pin;
}