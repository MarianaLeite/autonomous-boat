/**
 * @file location_service.h
 * @author Pierre Victor
 * @brief Service to manage location.
 * @version 0.1
 * @date 2023-10-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __LOCATION_SERVICE_H
#define __LOCATION_SERVICE_H

#define MASTER_BLE_NAME "MASTERBOAT"
#define MEASURED_POWER -69
#define SLAVE_BEACON_NAME_B1 "PSE2022_B1"
#define SLAVE_BEACON_NAME_B2 "PSE2022_B2"
#define SLAVE_BEACON_NAME_B3 "PSE2022_B3"
#define MAX_BEACONS 3

#include "stm32f4xx.h"
#include "Drivers/jdy18_driver.h"
#include <math.h>

typedef struct {
    float distance;
	char *name;
} Beacon_t;

/**
 * @brief Initialize the location service.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the BLE module.
 */
void LocationService_Init(UART_HandleTypeDef* huart);

/**
 * @brief Update the location.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the BLE module.
 */
void LocationService_Update(UART_HandleTypeDef* huart);

/**
 * @brief Calculate the distance between the beacon and the master.
 * 
 * @param rssi RSSI of the beacon.
 * @return float Distance between the beacon and the master.
 */
float LocationService_CalculateDistance(int rssi);

/**
 * @brief Scans and returns the mapped SLAVE_BEACON_NAME_B[1-3].
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the BLE module.
 * @return Beacon_t* Array with name and distance.
 */
Beacon_t* LocationService_Scan(UART_HandleTypeDef* huart);

#endif /* __LOCATION_SERVICE_H */
