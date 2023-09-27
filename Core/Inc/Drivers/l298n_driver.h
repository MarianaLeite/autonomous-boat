/**
 * @file l298n_driver.h
 * @author Mariana Leite
 * @brief 
 * @version 0.1
 * @date 2023-09-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __L298N_DRIVER_H
#define __L298N_DRIVER_H

#include <stdint.h>

#include "stm32f4xx.h"

typedef struct {
	TIM_HandleTypeDef* htim;
	uint32_t channel;
	GPIO_TypeDef* IN1_GPIO;
	uint16_t IN1_Pin;
	GPIO_TypeDef* IN2_GPIO;
	uint16_t IN2_Pin;
} L298N_HandleTypeDef;

/**
 * @brief Initialize the L298N module with the initial motor control parameters.
 * 
 * @param handler L298N_HandleTypeDef pointer to module handler.
 * @param period Initial timer period.
 */
void L298NDriver_Init(L298N_HandleTypeDef* handler, uint32_t period);

/**
 * @brief Set motor speed value.
 * 
 * @param handler L298N_HandleTypeDef pointer to module handler.
 * @param speed Relative speed of the motor, where 0.0 is the minimum speed and 1.0 the maximum speed.
 */
void L298NDriver_SetSpeed(L298N_HandleTypeDef* handler, float speed);

/**
 * @brief Set the motor direction to forward spin.
 * 
 * @param handler L298N_HandleTypeDef pointer to module handler.
 */
void L298NDriver_MoveForward(L298N_HandleTypeDef* handler);

/**
 * @brief Set the motor direction to backward spin.
 * 
 * @param handler L298N_HandleTypeDef pointer to module handler.
 */
void L298NDriver_MoveBackward(L298N_HandleTypeDef* handler);

/**
 * @brief Stop motor spin.
 * 
 * @param handler L298N_HandleTypeDef pointer to module handler.
 */
void L298NDriver_Stop(L298N_HandleTypeDef* handler);

#endif /* __L298N_DRIVER_H */
