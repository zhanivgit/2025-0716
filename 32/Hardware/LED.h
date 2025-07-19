#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Turn(void);
void LED_Blink(uint32_t duration_ms, uint8_t times);

#endif
