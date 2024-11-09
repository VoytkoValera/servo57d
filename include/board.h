#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x_it.h"
#include "n32l40x.h"
#include "n32l40x_i2c.h"
#include "oled.h"

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

/* Encoder MT6816 */

#define MT6816_PORT         GPIOB
#define MT6816_MOSI         GPIO_PIN_5
#define MT6816_MISO         GPIO_PIN_4
#define MT6816_CLK          GPIO_PIN_3
#define MT6816_CS           GPIO_PIN_6

/* Current ADC */

#define CURRENT_A           GPIO_PIN_2
#define CURRENT_B           GPIO_PIN_1

/* Stepper drivers */

#define PHASE_A_PORT        GPIOA
#define PHASE_A1_PIN        GPIO_PIN_6
#define PHASE_A2_PIN        GPIO_PIN_7
#define PHASE_B_PORT        GPIOB
#define PHASE_B1_PIN        GPIO_PIN_0
#define PHASE_B2_PIN        GPIO_PIN_1

/* Prototypes */

void board_init(void);
void oled_init(void);
void mt6816_init(void);
void stepper_init(void);


uint16_t mt6816_read(void);
// RTT print
void print_log(const char * sFormat, ...);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */