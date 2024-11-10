#include "board.h"
#include <stdlib.h>

static uint16_t cooldown_g = 100;
static uint16_t period_g = 205;

static int8_t speed_g = 0;

static const uint8_t phase_table[] = {0b0101, 0b0110, 0b1010, 0b1001};

void stepper_init(void) {
    GPIO_InitType GPIO_InitStructure;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    OCInitType TIM_OCInitStructure;
    NVIC_InitType NVIC_InitStructure;

    /* Enable TIM2 clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = PHASE_A1_PIN | PHASE_A2_PIN;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(PHASE_A_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = PHASE_B1_PIN | PHASE_B2_PIN;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(PHASE_B_PORT, &GPIO_InitStructure);

    /* TIM2 configuration */
    TIM_TimeBaseStructure.Period    = 0x100;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0x10;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);
    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OcMode = TIM_OCMODE_TIMING;
    TIM_OCInitStructure.Pulse  = 0x0;
    TIM_InitOc1(TIM2, &TIM_OCInitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_UPDATE);

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ConfigInt(TIM2, TIM_INT_UPDATE, ENABLE);
    TIM_Enable(TIM2, ENABLE);
}

static void set_driver(uint8_t val) {
    uint16_t setval = PHASE_A_PORT->POD;

    if (val&1)
        setval |= PHASE_A1_PIN;
    else
        setval &= ~PHASE_A1_PIN;

    if (val&2)
        setval |= PHASE_A2_PIN;
    else
        setval &= ~PHASE_A2_PIN;
    PHASE_A_PORT->POD = setval;

    setval = PHASE_B_PORT->POD;
    if (val&4)
        setval |= PHASE_B1_PIN;
    else
        setval &= ~PHASE_B1_PIN;

    if (val&8)
        setval |= PHASE_B2_PIN;
    else
        setval &= ~PHASE_B2_PIN;
    PHASE_B_PORT->POD = setval;
}

static void step_tick() {
    static uint16_t cooldown = 200;
    static uint16_t period = 205;
    static uint8_t  phase = 0;

    if (cooldown > 0) {
        set_driver(0);
        cooldown--;
    } else {
        if (speed_g != 0) {
            set_driver(phase_table[phase]);
        } else {
            set_driver(0);
        }
    }

    if (period > 0) {
        period--;
    } else {
        period = period_g;
        cooldown = cooldown_g;
        if (speed_g > 0) {
            phase++;
            if (phase>3) phase = 0;
        } else {
            if (phase == 0)
                phase = 4;
            phase--;
        }
    }
}

void TIM2_IRQHandler(void) {
    static uint8_t val = 0;
    TIM_ClrIntPendingBit(TIM2, TIM_INT_UPDATE);
    val ^= 1;
    ext_set(EXT6_PIN, val);
    step_tick();
}

void stepper_set_speed(int8_t speed) {
    speed_g = speed;
}