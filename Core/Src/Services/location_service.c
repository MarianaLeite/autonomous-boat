/**
 * @file location_service.c
 * @author Pierre Victor
 * 		   Mariana Leite
 * @brief 
 * @version 0.1
 * @date 2023-11-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Services/location_service.h"
#include "Drivers/jdy18_driver.h"
#include "Services/data_filter_service.h"

#include <math.h>

JDY18_HandleTypeDef bleHandler;

buffer_t b1Buffer;
buffer_t b2Buffer;
buffer_t b3Buffer;

void LocationService_Init(UART_HandleTypeDef *huart, TIM_HandleTypeDef* htim)
{
	bleHandler.huart = huart;
	bleHandler.name = MASTER_BLE_NAME;
	bleHandler.baudRate = BAUD_9600;
	bleHandler.role = MASTER;
	bleHandler.parity = NO_PARITY;
	bleHandler.stopBit = 0;

	JDY18Driver_Init(&bleHandler);
	JDY18Driver_InquireDevices(bleHandler.huart);

	HAL_TIM_Base_Start_IT(htim);
}

float LocationService_CalculateDistance(int rssi)
{
	return pow(10, ((MEASURED_POWER - rssi) / 20));
}

void LocationService_UpdateLocation()
{
	scan_t scannedDevices;
	float b1Distance, b2Distance, b3Distance;

	JDY18Driver_GetScannedDevices(&scannedDevices);

	for(size_t i = 0; i < scannedDevices.size; i++) {
		char* deviceName = scannedDevices.devices[i].name;
		int rssi = scannedDevices.devices[i].rssi;

		if(strstr(deviceName, SLAVE_BEACON_NAME_B1) == 0) {
			b1Distance = DataFilterService_MovingAverage(&b1Buffer, LocationService_CalculateDistance(rssi));
		} else if(strstr(deviceName, SLAVE_BEACON_NAME_B2) == 0) {
			b2Distance = DataFilterService_MovingAverage(&b2Buffer, LocationService_CalculateDistance(rssi));
		} else if(strstr(deviceName, SLAVE_BEACON_NAME_B3) == 0) {
			b3Distance = DataFilterService_MovingAverage(&b3Buffer, LocationService_CalculateDistance(rssi));
		}
	}

	// Calculates system location

	JDY18Driver_InquireDevices(bleHandler.huart);
}
