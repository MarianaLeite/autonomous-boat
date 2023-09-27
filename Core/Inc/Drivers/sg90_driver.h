/**
 * @file sg90_driver.h
 * @author Pierre Victor
 * @brief Driver to controller SG90 9g Micro Servo.
 * @version 0.1
 * @date 2023-09-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __SG90_DRIVER_H
#define __SG90_DRIVER_H

#include <stdint.h>

#include "stm32f4xx.h"

/**
 * @brief Set the position of Micro Servo using degrees.
 * 
 * @param htim TIM_HandleTypeDef pointer to timer handler associated to the PWM.
 * @param channel Timer channel associated to the PWM.
 * @param degrees Position servo in degrees.
 */
void SG90Driver_SetPosition(TIM_HandleTypeDef* htim, uint32_t channel, int8_t degrees);

#endif /* __SG90_DRIVER_H */
