#include "Services/beacons_service.h"
#include "Drivers/jdy18_driver.h"

Beacon_t *beacons[MAX_BEACONS];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);
		HAL_UART_DMAStop(huart);
		BeaconsService_Update(huart);
	}
}

void BeaconsService_Init(UART_HandleTypeDef *huart)
{
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
	HAL_UART_Receive_DMA(huart, uartBeaconBuffer, sizeof(uartBeaconBuffer));

	JDY18Driver_SetRole(huart, MASTER);
	HAL_Delay(200);
	JDY18Driver_SetParity(huart, NO_PARITY);
	HAL_Delay(200);
	JDY18Driver_SetBaudRate(huart, BAUD_9600);
	HAL_Delay(200);
	JDY18Driver_SetName(huart, MASTER_BLE_NAME);
	HAL_Delay(200);
	JDY18Driver_SetStopBit(huart, 0);
	HAL_Delay(200);
	memset(uartBeaconBuffer, 0, sizeof(uartBeaconBuffer));
}

void BeaconsService_Update(UART_HandleTypeDef *huart)
{
	// execute this if END_RESPONSE_SCAN or uartBeaconBuffer is full
	memset(uartBeaconBuffer, 0, sizeof(uartBeaconBuffer));
	HAL_UART_Receive_DMA(huart, uartBeaconBuffer, sizeof(uartBeaconBuffer));
}

float BeaconsService_CalculateDistance(int rssi)
{
	return pow(10, ((MEASURED_POWER - rssi) / 20));
}

Beacon_t *BeaconsService_GetAll(UART_HandleTypeDef *huart)
{
	return *beacons;
}
