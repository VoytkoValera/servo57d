#include "board.h"
#include <stdlib.h>

static uint16_t buf[2];

void mt6816_init(void) {
    SPI_InitType SPI_InitStructure;
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = MT6816_MISO;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_SPI1;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Input;
    GPIO_InitPeripheral(MT6816_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = MT6816_MOSI;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(MT6816_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = MT6816_CLK;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_SPI1;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(MT6816_PORT, &GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin          = MT6816_CS;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(MT6816_PORT, &GPIO_InitStructure);
    MT6816_PORT->PBSC = MT6816_CS; // CS High

    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_16BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_4;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Enable(SPI1, ENABLE);
}

uint16_t mt6816_read(void) {
    buf[0] = 0x8300;
    buf[1] = 0x8400;
    MT6816_PORT->PBC = MT6816_CS; // CS Low
    MT6816_PORT->PBC = MT6816_CS; // CS Low
    SPI_I2S_TransmitData(SPI1, buf[0]);
    while (SPI_I2S_GetStatus(SPI1, SPI_I2S_RNE_FLAG) == RESET);
    buf[0] = SPI_I2S_ReceiveData(SPI1);
    MT6816_PORT->PBSC = MT6816_CS; // CS High
    MT6816_PORT->PBSC = MT6816_CS; // CS High

    MT6816_PORT->PBC = MT6816_CS; // CS Low
    MT6816_PORT->PBC = MT6816_CS; // CS Low
    SPI_I2S_TransmitData(SPI1, buf[1]);
    while (SPI_I2S_GetStatus(SPI1, SPI_I2S_RNE_FLAG) == RESET);
    buf[1] = SPI_I2S_ReceiveData(SPI1);
    MT6816_PORT->PBSC = MT6816_CS; // CS High
    uint16_t sample = ((buf[0] & 0x00FF) << 8) | (buf[1] & 0x00FF);
    print_log("RX %04x\n", sample);
    return sample>>2;
}
