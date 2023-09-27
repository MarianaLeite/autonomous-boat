#ifndef __PWM_SERVICE_H
#define __PWM_SERVICE_H

#include <stdint.h>

#include "stm32f4xx.h"

void PwmService_SetPeriod(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t period);
void PwmService_SetDutyCycle(TIM_HandleTypeDef* htim, uint32_t channel, float duty_cycle);

#endif /* __PWM_SERVICE_H */
