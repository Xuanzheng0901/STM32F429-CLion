#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"
#include "adc.h"
#include "usart.h"
#include <stdio.h>
#include "string.h"

void Error_Handler(void);
void app_main(void);

#endif
