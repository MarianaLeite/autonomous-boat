/**
 * @file pwm_service.c
 * @author Mariana Leite
 * @brief 
 * @version 0.1
 * @date 2023-09-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Services/pwm_service.h"

void PwmService_SetPeriod(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t period)
{
	HAL_TIM_PWM_Stop(htim, channel);

	htim->Init.Period = period;
	HAL_TIM_PWM_Init(htim);

	HAL_TIM_PWM_Start(htim, channel);
}

void PwmService_SetDutyCycle(TIM_HandleTypeDef* htim, uint32_t channel, float duty_cycle)
{
	HAL_TIM_PWM_Stop(htim, channel);

	uint32_t pulse = duty_cycle*htim->Init.Period;

	TIM_OC_InitTypeDef sConfigOC = {0};
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulse;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, channel);

	HAL_TIM_PWM_Start(htim, channel);
}
