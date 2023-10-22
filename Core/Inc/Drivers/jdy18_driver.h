/**
 * @file jdy18_driver.h
 * @author Pierre Victor
 * @brief Driver to Bluetooth 4.2 BLE module.
 * @version 0.1
 * @date 2023-10-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __JDY18_DRIVER_H
#define __JDY18_DRIVER_H

#define MAX_SIZE_DATA 30
#define INIT_MODULE_RESPONSE_SCAN "+DEV:"
#define END_RESPONSE_SCAN "+STOP:SCAN"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f4xx.h"

typedef enum {
	SET_NAME,
	SET_BAUD_RATE,
	SET_ROLE,
	SET_PARITY,
	SET_STOP_BIT,
	MASTER_SCAN_SLAVE
} AtInstruction_t;

typedef enum {
	BAUD_1200 = 1,
	BAUD_2400 = 2,
	BAUD_4800 = 3,
	BAUD_9600 = 4,
	BAUD_19200 = 5,
	BAUD_38400 = 6,
	BAUD_57600 = 7,
	BAUD_115200 = 8,
	BAUD_230400 = 9
} BaudRate_t;

typedef enum {
	SLAVE = 0,
    MASTER = 1,
    IBEACON = 3,
} RoleParam_t;

typedef enum {
	NO_PARITY,
    ODD_PARITY,
    EVEN_PARITY,
} ParityParam_t;

/**
 * @brief Send data to Bluetooth module.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 * @param data Data to send to Bluetooth module.
 */
void JDY18Driver_SendData(UART_HandleTypeDef* huart, char *data);

/**
 * @brief Set the name of Bluetooth module.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 * @param name  Name of Bluetooth module.
 */
void JDY18Driver_SetName(UART_HandleTypeDef* huart, char *name);

/**
 * @brief Set the baud rate of Bluetooth module.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 * @param baudRate Baud rate of Bluetooth module.
 */
void JDY18Driver_SetBaudRate(UART_HandleTypeDef* huart, BaudRate_t baudRate);

/**
 * @brief Set the role of Bluetooth module.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 * @param role Role of Bluetooth module.
 */
void JDY18Driver_SetRole(UART_HandleTypeDef* huart, RoleParam_t role);

/**
 * @brief Set the parity of Bluetooth module.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 * @param parity Parity of Bluetooth module.
 */
void JDY18Driver_SetParity(UART_HandleTypeDef* huart, ParityParam_t parity);

/**
 * @brief Set the stop bit of Bluetooth module.
 * 
 * @param huart UART_HandleTypeDef pointer to UART handler associated to the Bluetooth module.
 * @param stopBit Stop bit of Bluetooth module.
 */
void JDY18Driver_SetStopBit(UART_HandleTypeDef* huart, uint8_t stopBit);

#endif /* __JDY18_DRIVER_H */
