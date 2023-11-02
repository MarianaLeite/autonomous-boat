/**
 * @file location_service.h
 * @author Pierre Victor
 *         Mariana Leite
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
#define SLAVE_BEACON_NAME_B1 "PSE2022_B1"
#define SLAVE_BEACON_NAME_B2 "PSE2022_B2"
#define SLAVE_BEACON_NAME_B3 "PSE2022_B3"

#define MEASURED_POWER -82

#include "stm32f4xx.h"

/**
 * @brief Initialize location service.
 * 
 * @param huart UART_HandleTypeDef pointer to serial handler structure.
 * @param htim TIM_HandleTypeDef pointer to timer handler structure.
 */
void LocationService_Init(UART_HandleTypeDef* huart, TIM_HandleTypeDef* htim);

/**
 * @brief Calculate the distance between the beacon and the master.
 * 
 * @param rssi RSSI of the beacon.
 * @return float Distance between the beacon and the master.
 */
float LocationService_CalculateDistance(int rssi);

/**
 * @brief Calculates and updates the system location.
 * 
 */
void LocationService_UpdateLocation();

#endif /* __LOCATION_SERVICE_H */
