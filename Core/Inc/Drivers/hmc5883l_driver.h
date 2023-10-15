/**
 * @file hmc5883l_driver.h
 * @author João Gomes
 * @brief Driver to communicate with HMC5883L.
 * @version 0.1
 * @date 2023-10-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef INC_DRIVERS_HMC5883L_DRIVER_H
#define INC_DRIVERS_HMC5883L_DRIVER_H

#include "stm32f4xx_hal.h"
#include "stdbool.h"

#define HMC5883l_ADDRESS       (0x3D)
#define HMC5883l_CONF_REG_A    (0x00)
#define HMC5883l_CONF_REG_B    (0x01)
#define HMC5883l_MODE_REG      (0x02)
#define HMC5883l_DATAX_MSB_REG (0x03)
#define HMC5883l_DATAX_LSB_REG (0x04)
#define HMC5883l_DATAZ_MSB_REG (0x05)
#define HMC5883l_DATAZ_LSB_REG (0x06)
#define HMC5883l_DATAY_MSB_REG (0x07)
#define HMC5883l_DATAY_LSB_REG (0x08)
#define HMC5883l_STATUS_REG    (0x09)

typedef struct
{
	int16_t x_axis;
	int16_t y_axis;
	int16_t z_axis;
} HMC5883L_DataTypeDef;

typedef enum
{
	HMC5883L_1_SAMPLES_AVG,
	HMC5883L_2_SAMPLES_AVG,
	HMC5883L_4_SAMPLES_AVG,
	HMC5883L_8_SAMPLES_AVG
} HMC5883L_SamplesAvgTypeDef;

typedef enum
{
	HMC5883L_OUTPUT_RATE_0_75_HZ,
	HMC5883L_OUTPUT_RATE_1_5_HZ,
	HMC5883L_OUTPUT_RATE_3_HZ,
	HMC5883L_OUTPUT_RATE_7_5_HZ,
	HMC5883L_OUTPUT_RATE_15_HZ, // Default
	HMC5883L_OUTPUT_RATE_30_HZ,
	HMC5883L_OUTPUT_RATE_75_HZ
} HMC5883L_OutputRateTypeDef;

typedef enum
{
	// Normal measurement configuration (Default). In normal measurement configuration the device follows normal measurement flow. The positive and negative pins of the resistive load are left floating and high impedance.
	HMC5883L_MEASUREMENT_MODE_NORMAL,
	// Positive bias configuration for X, Y, and Z axes. In this configuration, a positive current is forced across the resistive load for all three axes.
	HMC5883L_MEASUREMENT_MODE_POSITIVE,
	// Negative bias configuration for X, Y and Z axes. In this configuration, a negative current is forced across the resistive load for all three axes..
	HMC5883L_MEASUREMENT_MODE_NEGATIVE
} HMC5883L_MeasurementModeTypeDef;

typedef enum
{
	HMC5883L_GAIN_0_88_GA,
	HMC5883L_GAIN_1_3_GA,
	HMC5883L_GAIN_1_9_GA,
	HMC5883L_GAIN_2_5_GA,
	HMC5883L_GAIN_4_0_GA,
	HMC5883L_GAIN_4_7_GA,
	HMC5883L_GAIN_5_6_GA,
	HMC5883L_GAIN_8_1_GA
} HMC5883L_GainTypeDef;

typedef enum
{
	HMC5883L_I2C_NORMAL_SPEED,
	HMC5883L_I2C_FAST_SPEED
} HMC5883L_I2cSpeedTypeDef;

typedef enum
{
	HMC5883L_CONTINUOUS_MEASUREMENT_MODE,
	HMC5883L_SINGLE_MEASUREMENT_MODE,
	HMC5883L_IDLE_MEASUREMENT_MODE
} HMC5883L_OperationModeTypeDef;

typedef struct
{
	I2C_HandleTypeDef *hi2c;
	HMC5883L_SamplesAvgTypeDef samples_avg;
	HMC5883L_OutputRateTypeDef output_rate;
	HMC5883L_MeasurementModeTypeDef measurement_mode;
	HMC5883L_GainTypeDef gain;
	HMC5883L_I2cSpeedTypeDef i2c_speed;
	HMC5883L_OperationModeTypeDef operation_mode;

} HMC5883L_HandlerTypeDef;

/**
 * @brief Initialize the HMC5883L module with the provided configurations.
 * 
 * @param handler HMC5883L_HandlerTypeDef pointer to module handler
 * @param timeout Timeout duration
 */
void HMC5883LDriver_Init(HMC5883L_HandlerTypeDef *handler, uint32_t timeout);

/**
 * @brief Read current axis values
 * 
 * @param handler HMC5883L_HandlerTypeDef pointer to module handler
 * @param data HMC5883L_DataTypeDef pointer to read data
 * @param timeout Timeout duration
 */
bool HMC5883LDriver_Read(HMC5883L_HandlerTypeDef *handler, HMC5883L_DataTypeDef *data, uint32_t timeout);

#endif /* INC_DRIVERS_HMC5883L_DRIVER_H */
