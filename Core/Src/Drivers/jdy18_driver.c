#include "Drivers/jdy18_driver.h"

char *atInstructions[] = {
	"AT+NAME",
	"AT+BAUD",
	"AT+ROLE",
	"AT+PARITY",
	"AT+USTP",
	"AT+INQ"
};

void JDY18Driver_SendData(UART_HandleTypeDef* huart, char *data) {
	char package[MAX_SIZE_DATA + 4];
	memset(package, 0, MAX_SIZE_DATA + 4);
	sprintf(package, "%s\r\n", data);
	HAL_UART_Transmit(huart, (uint8_t*)package, strlen(package), HAL_MAX_DELAY);
}

void JDY18Driver_SetName(UART_HandleTypeDef* huart, char *name) {
	char *instruction = atInstructions[SET_NAME];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%s", instruction, name);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetBaudRate(UART_HandleTypeDef* huart, BaudRate_t baudRate) {
	char *instruction = atInstructions[SET_BAUD_RATE];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, baudRate);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetRole(UART_HandleTypeDef* huart, RoleParam_t role) {
	char *instruction = atInstructions[SET_ROLE];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, role);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetParity(UART_HandleTypeDef* huart, ParityParam_t parity) {
	char *instruction = atInstructions[SET_PARITY];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, parity);
	JDY18Driver_SendData(huart, data);
}

void JDY18Driver_SetStopBit(UART_HandleTypeDef* huart, uint8_t stopBit) {
	char *instruction = atInstructions[SET_STOP_BIT];
	char data[MAX_SIZE_DATA];
	memset(data, 0, MAX_SIZE_DATA);
	sprintf(data, "%s%d", instruction, stopBit);
	JDY18Driver_SendData(huart, data);
}
