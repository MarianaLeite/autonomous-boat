/**
 * @file l293d_driver.c
 * @author Mariana Leite
 * @brief 
 * @version 0.1
 * @date 2023-09-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Drivers/l293d_driver.h"
#include "Services/pwm_service.h"

void L293DDriver_Init(L293D_HandleTypeDef* handler, uint32_t period)
{
	PwmService_SetPeriod(handler->htim, handler->channel, period);
}

void L293DDriver_SetSpeed(L293D_HandleTypeDef* handler, float speed)
{
	PwmService_SetDutyCycle(handler->htim, handler->channel, speed);
}

void L293DDriver_SendControl(L293D_HandleTypeDef* handler, L293D_Control control)
{
	HAL_GPIO_WritePin(handler->EN_GPIO, handler->EN_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(handler->LATCH_GPIO, handler->LATCH_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(handler->SER_GPIO, handler->SER_Pin, GPIO_PIN_RESET);

	uint8_t mask = 0x80;
	for(uint8_t i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(handler->CLK_GPIO, handler->CLK_Pin, GPIO_PIN_RESET);
		if(control & mask) {
			HAL_GPIO_WritePin(handler->SER_GPIO, handler->SER_Pin, GPIO_PIN_SET);
		} else {
			HAL_GPIO_WritePin(handler->SER_GPIO, handler->SER_Pin, GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(handler->CLK_GPIO, handler->CLK_Pin, GPIO_PIN_SET);
		mask >>= 1;
	}

	HAL_GPIO_WritePin(handler->LATCH_GPIO, handler->LATCH_Pin, GPIO_PIN_SET);
}
