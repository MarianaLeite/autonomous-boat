/**
 * @file control_service.h
 * @author Pierre Victor
 * @brief Service to control the boat.
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CONTROL_SERVICE_H
#define __CONTROL_SERVICE_H

#include "stm32f4xx.h"
#include "Drivers/l293d_driver.h"
#include "Drivers/sg90_driver.h"
#include "Services/location_service.h"
#include "Services/compass_service.h"

#define K_P 1.0

typedef struct
{
	UART_HandleTypeDef* huartLocation;
	TIM_HandleTypeDef* htimLocation;
	I2C_HandleTypeDef* hi2cCompass;
	TIM_HandleTypeDef* htimCompass;
	TIM_HandleTypeDef* htimServo;
	uint32_t channelServo;
	TIM_HandleTypeDef* htimMotor;
	uint32_t periodMotor;
} ControlParamsHandleTypeDef;

/**
 * @brief Initialize the control service.
 * Initialize the sensors and the actuators.
 * Must set the servo to 0° and wait 10s. After, navigate in a straight line for 10s.
 * 
 * @param handler 
 */
void ControlService_Init(ControlParamsHandleTypeDef* handler);


/**
 * @brief Control the boat with the proportional method.
 * 
 */
void ControlService_Proportional(ControlParamsHandleTypeDef* handler);

#endif /* __CONTROL_SERVICE_H */
