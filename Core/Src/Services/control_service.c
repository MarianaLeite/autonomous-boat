/**
 * @file control_service.c
 * @author Pierre Victor
 * @brief 
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Services/control_service.h"
#include "stdbool.h"
#include "main.h"

bool isMoving = false;
L293D_HandleTypeDef handlerMotor;

void ControlService_Init(ControlParamsHandleTypeDef* handler)
{
	handler->channelServo = TIM_CHANNEL_1;

	handlerMotor.htim = handler->htimMotor;
	handlerMotor.channel = TIM_CHANNEL_2;
	handlerMotor.EN_GPIO = L293D_EN_GPIO_Port;
	handlerMotor.EN_Pin = L293D_EN_Pin;
	handlerMotor.LATCH_GPIO = L293D_LATCH_GPIO_Port;
	handlerMotor.LATCH_Pin = L293D_LATCH_Pin;
	handlerMotor.CLK_GPIO = L293D_CLK_GPIO_Port;
	handlerMotor.CLK_Pin = L293D_CLK_Pin;
	handlerMotor.SER_GPIO = L293D_SER_GPIO_Port;
	handlerMotor.SER_Pin = L293D_SER_Pin;

	LocationService_Init(handler->huartLocation, handler->htimLocation);
	CompassService_Init(handler->hi2cCompass, handler->htimCompass);
	SG90Driver_SetPosition(handler->htimServo, handler->channelServo, 0);
	L293DDriver_Init(&handlerMotor, handler->periodMotor);
	L293DDriver_SetSpeed(&handlerMotor, 1.0);
	HAL_Delay(30000);
	L293DDriver_SendControl(&handlerMotor, M1_FORWARD);
	HAL_Delay(15000);
	L293DDriver_SendControl(&handlerMotor, M1_STOP);
}

void ControlService_Proportional(ControlParamsHandleTypeDef* handler)
{
	location_t masterLocation = LocationService_GetLocation();
	
	if (masterLocation.latitude == 0 || LocationService_IsInDestiny() == 1) {
		if (isMoving) {
			isMoving = !isMoving;
			L293DDriver_SendControl(&handlerMotor, M1_STOP);
		}
	} else {
		float rudderDegrees = (CompassService_GetCompassAngle() - LocationService_GetArrivalAngle()) * K_P;

		SG90Driver_SetPosition(handler->htimServo, handler->channelServo, (int16_t) rudderDegrees);
		if (!isMoving) {
			isMoving = !isMoving;
			L293DDriver_SendControl(&handlerMotor, M1_FORWARD);
		}
	}
}
