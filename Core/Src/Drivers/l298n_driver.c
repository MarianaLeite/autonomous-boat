/**
 * @file l298n_driver.c
 * @author Mariana Leite
 * @brief 
 * @version 0.1
 * @date 2023-09-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Drivers/l298n_driver.h"

#include "Services/pwm_service.h"

void L298NDriver_Init(L298N_HandleTypeDef* handler, uint32_t period)
{
	PwmService_SetPeriod(handler->htim, handler->channel, period);
}

void L298NDriver_SetSpeed(L298N_HandleTypeDef* handler, float speed)
{
	PwmService_SetDutyCycle(handler->htim, handler->channel, speed);
}

void L298NDriver_MoveForward(L298N_HandleTypeDef* handler)
{
	HAL_GPIO_WritePin(handler->IN1_GPIO, handler->IN1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(handler->IN2_GPIO, handler->IN2_Pin, GPIO_PIN_RESET);
}

void L298NDriver_MoveBackward(L298N_HandleTypeDef* handler)
{
	HAL_GPIO_WritePin(handler->IN1_GPIO, handler->IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(handler->IN2_GPIO, handler->IN2_Pin, GPIO_PIN_SET);
}

void L298NDriver_Stop(L298N_HandleTypeDef* handler)
{
	HAL_GPIO_WritePin(handler->IN1_GPIO, handler->IN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(handler->IN2_GPIO, handler->IN2_Pin, GPIO_PIN_RESET);
}
