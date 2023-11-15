/**
 * @file compass_service.h
 * @author João Gomes
 * @brief
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef COMPASS_SERVICE_H_
#define COMPASS_SERVICE_H_

#include <stdint.h>
#include <math.h>

#include "stm32f4xx.h"

#define MAGNETIC_DECLINATION 0.3508

typedef struct
{
	int16_t xmin;
	int16_t xmax;
	int16_t ymin;
	int16_t ymax;
	int16_t x_offset;
	int16_t y_offset;
	float x_scale;
	float y_scale;
} CompassCalibrationParamsTypeDef;

/**
 * @brief Initializes compass service.
 * 
 * @param hi2c I2C_HandleTypeDef pointer to i2c peripheral used for magnetometer module communication.
 * @param htim TIM_HandleTypeDef pointer to timer where the compass angle should be updated periodically.
 */
void CompassService_Init(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* htim);

/**
 * @brief Calibrate magnetometer module over provided iterations.
 *
 * @param iterations Number of iterations (measures) used for calibration.
 */
void CompassService_Calibrate(int iterations);

/**
 * @brief Clean and setup calibration params.
 * 
 * @param calibrationParams CompassCalibrationParamsTypeDef pointer to stored calibration params.
 */
void CompassService_InitCalibrationParams(CompassCalibrationParamsTypeDef *calibrationParams);

/**
 * @brief Update calibration params with given axis measured values.
 * 
 * @param x_axis Measured value for X axis.
 * @param y_axis Measured value for Y axis.
 * @param calibrationParams CompassCalibrationParamsTypeDef pointer to stored calibration params.
 */
void CompassService_UpdateCalibrationParams(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibrationParams);

/**
 * @brief Calculate and return a normalized degress angle using X and Y axes.
 * 
 * @param x_axis Measured value for X axis.
 * @param y_axis Measured value for Y axis.
 * @param calibrationParams CompassCalibrationParamsTypeDef pointer to stored calibration params.
 * @return float Calculated angle.
 */
float CompassService_CalculateAngle(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibrationParams);

/**
 * @brief Reads magnetometer values and calculates compass angle.
 * 
 */
void CompassService_UpdateCompassAngle();

/**
 * @brief Returns the current compass angle.
 * 
 * @return float Calculated angle.
 */
float CompassService_GetCompassAngle();

#endif /* COMPASS_SERVICE_H_ */
