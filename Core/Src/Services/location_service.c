#include "Services/location_service.h"

Beacon_t *beacons[MAX_BEACONS];

void LocationService_Init(UART_HandleTypeDef *huart)
{
	JDY18Driver_Init(huart, MASTER_BLE_NAME, BAUD_9600, MASTER, NO_PARITY, 0);
}

void LocationService_Update(UART_HandleTypeDef *huart)
{
	// need implementation
}

float LocationService_CalculateDistance(int rssi)
{
	return pow(10, ((MEASURED_POWER - rssi) / 20));
}

Beacon_t *LocationService_Scan(UART_HandleTypeDef *huart)
{
	JDY18Driver_InquireDevices(huart);
	return *beacons;
}
