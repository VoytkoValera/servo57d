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

/* Buttons */
#ifdef SERVO57D
#define BTN_MENU_PORT   GPIOB
#define BTN_MENU_PIN    GPIO_PIN_9 /* Menu */
#define BTN_ENTER_PORT   GPIOB
#define BTN_ENTER_PIN    GPIO_PIN_8 /* Enter */
#define BTN_NEXT_PORT   GPIOA
#define BTN_NEXT_PIN    GPIO_PIN_15 /* Next */
#endif
#ifdef SERVO42D
#define BTN_MENU_PORT   GPIOA
#define BTN_MENU_PIN    GPIO_PIN_14 /* Menu */
#define BTN_ENTER_PORT   GPIOA
#define BTN_ENTER_PIN    GPIO_PIN_15 /* Enter */
#define BTN_NEXT_PORT   GPIOA
#define BTN_NEXT_PIN    GPIO_PIN_13 /* Next */
#endif


/* Externals */
#ifdef SERVO57D
#define EXT_DIR_PORT   GPIOA
#define EXT_DIR_PIN    GPIO_PIN_8 /* nDIR */
#define EXT_STEP_PORT   GPIOA
#define EXT_STEP_PIN    GPIO_PIN_0 /* nSTP */
#define EXT_EN_PORT   GPIOB
#define EXT_EN_PIN    GPIO_PIN_7 /* nEN */
#define EXT_IN1_PORT   GPIOB
#define EXT_IN1_PIN    GPIO_PIN_13 /* M_IN1 */
#define EXT_IN2_PORT   GPIOB
#define EXT_IN2_PIN    GPIO_PIN_12 /* M_IN2 */
#define EXT_OUT1_PORT   GPIOB
#define EXT_OUT1_PIN    GPIO_PIN_14 /* M_OUT1 */
#define EXT_OUT2_PORT   GPIOB
#define EXT_OUT2_PIN    GPIO_PIN_15 /* M_OUT2 */
#endif

#ifdef SERVO42D
#define EXT_DIR_PORT   GPIOA
#define EXT_DIR_PIN    GPIO_PIN_8 /* nDIR */
#define EXT_STEP_PORT   GPIOA
#define EXT_STEP_PIN    GPIO_PIN_0 /* nSTP */
#define EXT_EN_PORT   GPIOB
#define EXT_EN_PIN    GPIO_PIN_7 /* nEN */
#define EXT_IN1_PORT   GPIOA
#define EXT_IN1_PIN    GPIO_PIN_10 /* M_IN1 */
#endif


/* OLED ssd1306 */
#ifdef SERVO57D
// I2C Configuration
#define SSD1306_SCL_PORT    GPIOA
#define SSD1306_SCL_PIN     GPIO_PIN_4
#define SSD1306_SDA_PORT    GPIOA
#define SSD1306_SDA_PIN     GPIO_PIN_5
#define SSD1306_RESET_PORT  GPIOB
#define SSD1306_RESET_PIN   GPIO_PIN_2
#endif
#ifdef SERVO42D
#define SSD1306_SCL_PORT    GPIOA
#define SSD1306_SCL_PIN     GPIO_PIN_4
#define SSD1306_SDA_PORT    GPIOA
#define SSD1306_SDA_PIN     GPIO_PIN_5
#define SSD1306_RESET_PORT  GPIOA
#define SSD1306_RESET_PIN   GPIO_PIN_9
#endif
#define SSD1306_I2C_ADDR    (0x3C << 1)
#define I2C_MASTER_ADDR     0x0

/* Encoder MT6816 */

#define MT6816_PORT         GPIOB
#define MT6816_MOSI         GPIO_PIN_5
#define MT6816_MISO         GPIO_PIN_4
#define MT6816_CLK          GPIO_PIN_3
#define MT6816_CS           GPIO_PIN_6


/* Current ADC */
#define CURRENT_PORT        GPIOA
#define CURRENT_A           GPIO_PIN_2
#define CURRENT_B           GPIO_PIN_1

/* Stepper drivers */

#define PHASE_A_PORT        GPIOA
#define PHASE_A1_PIN        GPIO_PIN_6
#define PHASE_A2_PIN        GPIO_PIN_7
#define PHASE_B_PORT        GPIOB
#define PHASE_B1_PIN        GPIO_PIN_0
#define PHASE_B2_PIN        GPIO_PIN_1

/* CAN */
#define CAN_RX_PORT            GPIOA
#define CAN_RX_PIN             GPIO_PIN_11
#define CAN_TX_PORT            GPIOA
#define CAN_TX_PIN             GPIO_PIN_12

/* Prototypes */
void board_init(void);
void oled_init(void);
void led_init(void);
void mt6816_init(void);
void stepper_init(void);
void buttons_init(void);
void external_init(void);
void can_init(void);

void buttons_tick(void);
void ext_set(uint16_t pin, uint8_t val);

void stepper_set_speed(int8_t speed);

uint16_t mt6816_read(void);
// RTT print
void print_log(const char * sFormat, ...);

void LedOn(void);
void LedOff(void);
void LedBlink(void);

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */