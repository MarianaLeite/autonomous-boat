/**
 * @file beacons_service.h
 * @author Pierre Victor
 * @brief Service to manage beacons.
 * @version 0.1
 * @date 2023-10-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __BEACONS_SERVICE_H
#define __BEACONS_SERVICE_H

#define MAX_SIZE_UART_BEACON_BUFFER 1000
#define MASTER_BLE_NAME "MASTERBOAT"
#define MEASURED_POWER -69
#define SLAVE_BEACON_NAME_B1 "PSE2022_B1"
#define SLAVE_BEACON_NAME_B2 "PSE2022_B2"
#define SLAVE_BEACON_NAME_B3 "PSE2022_B3"
#define MAX_BEACONS 3

#include "stm32f4xx.h"

#include <math.h>

typedef struct {
	char *mac;
	int rssi;
    float distance;
	char *name;
} Beacon_t;

uint8_t uartBeaconBuffer[MAX_SIZE_UART_BEACON_BUFFER];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/**
 * @brief Initialize the beacons service.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 */
void BeaconsService_Init(UART_HandleTypeDef* huart);

/**
 * @brief Update the beacons.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 */
void BeaconsService_Update(UART_HandleTypeDef* huart);

/**
 * @brief Calculate the distance between the beacon and the master.
 * 
 * @param rssi RSSI of the beacon.
 * @return float Distance between the beacon and the master.
 */
float BeaconsService_CalculateDistance(int rssi);

/**
 * @brief Get all the beacons.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 * @return Beacon_t* Array of beacons.
 */
Beacon_t* BeaconsService_GetAll(UART_HandleTypeDef* huart);

#endif /* __BEACONS_SERVICE_H */
