
#include "board.h"
#include <stdio.h>
#include <stdint.h>

TIM_TimeBaseInitType TIM_TimeBaseStructure;

/**
 * @brief  Inserts a delay time.
 * @param count specifies the delay time length.
 */
void Delay(uint32_t count)
{
    volatile uint32_t c = count;
    for (; c > 0; c--)
        ;
}

/**
 * @brief  Turns selected Led on as output low level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Turns selected Led Off as output high level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}
/**
 * @brief  Turns selected Led on or off.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be one of the following values:
 *  @arg GPIO_PIN_0~GPIO_PIN_15: set related pin on
 *      @arg (GPIO_PIN_0<<16)~(GPIO_PIN_15<<16): clear related pin off
 */
void LedOnOff(GPIO_Module* GPIOx, uint32_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Toggles the selected Led.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/**
 * @brief Assert failed function by user.
 * @param file The name of the call that failed.
 * @param line The source line number of the call that failed.
 */
#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT

/**
 * @brief  Configures tim1 clocks.
 */
void TIM_Configuration(void)
{
    /* Compute the prescaler value */
    uint16_t PrescalerValue = (uint16_t) (SystemCoreClock / 120000) - 1;

    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Period    = 65535;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_ConfigPrescaler(TIM1, PrescalerValue, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    /* TIM1 enable update irq */
    TIM_ConfigInt(TIM1, TIM_INT_UPDATE, ENABLE);

    /* TIM1 enable counter */
    TIM_Enable(TIM1, ENABLE);
}

int main(void)
{
    board_init();
    LedOn(LED1_PORT, LED1_PIN); /*Turn on Led1*/
    TIM_Configuration();
    oled_init();

    while (1)
    {
        

        /* Insert delay */
        Delay(0x28FFFF);
    }
}

/**
 * @brief  This function handles TIM1 update interrupt request.
 */
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetIntStatus(TIM1, TIM_INT_UPDATE) != RESET)
    {
        TIM_ClrIntPendingBit(TIM1, TIM_INT_UPDATE);

        LedBlink(LED1_PORT, LED1_PIN);
    }
}