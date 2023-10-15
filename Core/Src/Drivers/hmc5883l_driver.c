/**
 * @file hmc5883l_driver.c
 * @author João Marcos
 * @brief Driver to communicate with HMC5883L.
 * @version 0.1
 * @date 2023-10-14
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "Drivers/hmc5883l_driver.h"

void HMC5883LDriver_Init(HMC5883L_HandlerTypeDef *handler, uint32_t timeout)
{
	uint8_t config_reg_a = 0;
	uint8_t config_reg_b = 0;
	uint8_t mod_reg = 0;

	config_reg_a |= (handler->samples_avg & 0b11) << 5;
	config_reg_a |= (handler->output_rate & 0b111) << 2;
	config_reg_a |= (handler->measurement_mode & 0b111);

	config_reg_b |= (handler->gain & 0b111) << 5;

	mod_reg |= (handler->i2c_speed & 0b1) << 7;
	mod_reg |= (handler->operation_mode & 0b111);

	HAL_I2C_Mem_Write(handler->hi2c, HMC5883l_ADDRESS, HMC5883l_CONF_REG_A, 1, &config_reg_a, 1, timeout);
	HAL_I2C_Mem_Write(handler->hi2c, HMC5883l_ADDRESS, HMC5883l_CONF_REG_B, 1, &config_reg_b, 1, timeout);
	HAL_I2C_Mem_Write(handler->hi2c, HMC5883l_ADDRESS, HMC5883l_MODE_REG, 1, &mod_reg, 1, timeout);
}

bool HMC5883LDriver_Read(HMC5883L_HandlerTypeDef *handler, HMC5883L_DataTypeDef *data, uint32_t timeout)
{
	uint8_t buffer[6];

	HAL_I2C_Mem_Read(handler->hi2c, HMC5883l_ADDRESS, HMC5883l_STATUS_REG, 1, buffer, 1, timeout);

	if ((buffer[0] & 0x01) != 1) {
		return false;
	}

	HAL_I2C_Mem_Read(handler->hi2c, HMC5883l_ADDRESS, HMC5883l_DATAX_MSB_REG, 1, buffer, 6, timeout);

	data->x_axis = (buffer[0] << 8) | buffer[1];
	data->z_axis = (buffer[2] << 8) | buffer[3];
	data->y_axis = (buffer[0] << 4) | buffer[5];
	
	return true;
}
