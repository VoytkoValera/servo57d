#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x_it.h"
#include "n32l40x.h"
#include "n32l40x_i2c.h"

/* Board definitions */

/* Led1 - PD0 */
#define LED1_PORT   GPIOD
#define LED1_PIN    GPIO_PIN_0

/* OLED ssd1306 */

// I2C Configuration
#define SSD1306_SCL         GPIO_PIN_4
#define SSD1306_SDA         GPIO_PIN_5
#define SSD1306_RESET       GPIO_PIN_2
#define SSD1306_PORT        GPIOA
#define SSD1306_RPORT       GPIOB
#define SSD1306_I2C_ADDR    (0x3C << 1)
#define I2C_MASTER_ADDR     0x0
// The width of the screen can be set using this
// define. The default value is 128.
#define SSD1306_WIDTH           64

// If your screen horizontal axis does not start
// in column 0 you can use this define to
// adjust the horizontal offset
#define SSD1306_X_OFFSET        0

// The height can be changed as well if necessary.
// It can be 32, 64 or 128. The default value is 64.
#define SSD1306_HEIGHT          64


/* Encoder MT6816 */


void board_init(void);
void oled_init(void);

#endif /* __BOARD_H__ */