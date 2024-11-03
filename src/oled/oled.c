#include "board.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>  // For memcpy

#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

static __IO uint32_t I2CTimeout;
typedef enum
{
    C_READY = 0,
    C_START_BIT,
    C_STOP_BIT
} CommCtrl_t;
static CommCtrl_t Comm_Flag = C_READY;
static uint8_t err_code;

void oled_send(uint8_t addr, uint8_t *bytes, uint8_t len) {
    err_code = 0;
    I2CTimeout             = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY)) {
        if ((I2CTimeout--) == 0) {
            err_code = 1;
            return;
        }
    }

    if (Comm_Flag == C_READY) {
        Comm_Flag = C_START_BIT;
        I2C_GenerateStart(I2C1, ENABLE);
    }

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_MODE_FLAG)) { // EV5
        if ((I2CTimeout--) == 0) {
            err_code = 2;
            return;
        }
    }

    I2C_SendAddr7bit(I2C1, SSD1306_I2C_ADDR, I2C_DIRECTION_SEND);
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_TXMODE_FLAG)) { // EV6
        if ((I2CTimeout--) == 0) {
            err_code = 3;
            return;
        }
    }
    Comm_Flag = C_READY;

    // Addr
    I2C_SendData(I2C1, addr);
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_SENDING)) {// EV8
        if ((I2CTimeout--) == 0) {
            err_code = 4;
            return;
        }
    }

    // Data
    while (len-- > 0) {
        I2C_SendData(I2C1, *bytes++);
        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_SENDING)) {// EV8
            if ((I2CTimeout--) == 0) {
                err_code = 5;
                return;
            }
        }
    }

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_SENDED)) {// EV8-2
        if ((I2CTimeout--) == 0) {
            err_code = 6;
            return;
        }
    }

    if (Comm_Flag == C_READY) {
        Comm_Flag = C_STOP_BIT;
        I2C_GenerateStop(I2C1, ENABLE);
    }
    
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY)) {
        if ((I2CTimeout--) == 0) {
            err_code = 7;
            return;
        }
    }
    Comm_Flag = C_READY;
}

// Send a byte to the command register
void ssd1306_WriteCommand(uint8_t byte) {
    oled_send(0, &byte, 1);
}

// Send data
void ssd1306_WriteData(uint8_t* buffer, size_t buff_size) {
    oled_send(0x40, buffer, buff_size);
}

void ssd1306_SetContrast(const uint8_t value) {
    const uint8_t kSetContrastControlRegister = 0x81;
    ssd1306_WriteCommand(kSetContrastControlRegister);
    ssd1306_WriteCommand(value);
}

/* Initialize the oled screen */
void oled_init(void) {
    ssd1306_WriteCommand(0xAE); //display off

    ssd1306_WriteCommand(0x20); //Set Memory Addressing Mode
    ssd1306_WriteCommand(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
                                // 10b,Page Addressing Mode (RESET); 11b,Invalid

    ssd1306_WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7

#ifdef SSD1306_MIRROR_VERT
    ssd1306_WriteCommand(0xC0); // Mirror vertically
#else
    ssd1306_WriteCommand(0xC8); //Set COM Output Scan Direction
#endif

    ssd1306_WriteCommand(0x00); //---set low column address
    ssd1306_WriteCommand(0x10); //---set high column address

    ssd1306_WriteCommand(0x40); //--set start line address - CHECK

    ssd1306_SetContrast(0xFF);

#ifdef SSD1306_MIRROR_HORIZ
    ssd1306_WriteCommand(0xA0); // Mirror horizontally
#else
    ssd1306_WriteCommand(0xA1); //--set segment re-map 0 to 127 - CHECK
#endif

#ifdef SSD1306_INVERSE_COLOR
    ssd1306_WriteCommand(0xA7); //--set inverse color
#else
    ssd1306_WriteCommand(0xA6); //--set normal color
#endif

// Set multiplex ratio.
#if (SSD1306_HEIGHT == 128)
    // Found in the Luma Python lib for SH1106.
    ssd1306_WriteCommand(0xFF);
#else
    ssd1306_WriteCommand(0xA8); //--set multiplex ratio(1 to 64) - CHECK
#endif

#if (SSD1306_HEIGHT == 32)
    ssd1306_WriteCommand(0x1F); //
#elif (SSD1306_HEIGHT == 64)
    ssd1306_WriteCommand(0x3F); //
#elif (SSD1306_HEIGHT == 128)
    ssd1306_WriteCommand(0x3F); // Seems to work for 128px high displays too.
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    ssd1306_WriteCommand(0xD3); //-set display offset - CHECK
    ssd1306_WriteCommand(0x00); //-not offset

    ssd1306_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
    ssd1306_WriteCommand(0xF0); //--set divide ratio

    ssd1306_WriteCommand(0xD9); //--set pre-charge period
    ssd1306_WriteCommand(0x22); //

    ssd1306_WriteCommand(0xDA); //--set com pins hardware configuration - CHECK
#if (SSD1306_HEIGHT == 32)
    ssd1306_WriteCommand(0x02);
#elif (SSD1306_HEIGHT == 64)
    ssd1306_WriteCommand(0x12);
#elif (SSD1306_HEIGHT == 128)
    ssd1306_WriteCommand(0x12);
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1306_WriteCommand(0xDB); //--set vcomh
    ssd1306_WriteCommand(0x20); //0x20,0.77xVcc

    ssd1306_WriteCommand(0x8D); //--set DC-DC enable
    ssd1306_WriteCommand(0x14); //
    ssd1306_WriteCommand(0xAF); //--turn on SSD1306 panel
}