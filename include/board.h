#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"

/* Board pin definitions */

/* Led1-PD0 */
#define PORT_GROUP1 GPIOD
#define LED1_PORT   PORT_GROUP1
#define LED1_PIN    GPIO_PIN_0


#endif /* __BOARD_H__ */