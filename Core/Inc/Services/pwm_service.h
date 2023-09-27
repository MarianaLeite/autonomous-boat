/**
 * @file pwm_service.h
 * @author Mariana Leite
 * @brief 
 * @version 0.1
 * @date 2023-09-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __PWM_SERVICE_H
#define __PWM_SERVICE_H

#include <stdint.h>

#include "stm32f4xx.h"

/**
 * @brief Set period of the PWM.
 * 
 * @param htim TIM_HandleTypeDef pointer to timer handler associated to the PWM.
 * @param channel Timer channel associated to the PWM.
 * @param period Timer counter.
 */
void PwmService_SetPeriod(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t period);

/**
 * @brief Set duty cycle of the PWM.
 * 
 * @param htim TIM_HandleTypeDef pointer to timer handler associated to the PWM.
 * @param channel Timer channel associated to the PWM.
 * @param duty_cycle Duty cycle of the PWM within [0-1] range
 */
void PwmService_SetDutyCycle(TIM_HandleTypeDef* htim, uint32_t channel, float duty_cycle);

#endif /* __PWM_SERVICE_H */
