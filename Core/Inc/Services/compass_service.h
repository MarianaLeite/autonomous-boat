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

#include "Drivers/hmc5883l_driver.h"

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
 * @brief Clean and setup calibration params.
 * 
 * @param calibration_params CompassCalibrationParamsTypeDef pointer to stored calibration params.
 */
void CompassService_InitCalibrationParams(CompassCalibrationParamsTypeDef *calibration_params);

/**
 * @brief Update calibration params with given axis measured values.
 * 
 * @param x_axis Measured value for X axis.
 * @param y_axis Measured value for Y axis.
 * @param calibration_params CompassCalibrationParamsTypeDef pointer to stored calibration params.
 */
void CompassService_Calibrate(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibration_params);

/**
 * @brief Calculate and return a normalized degress angle using X and Y axes.
 * 
 * @param x_axis Measured value for X axis.
 * @param y_axis Measured value for Y axis.
 * @param calibration_params CompassCalibrationParamsTypeDef pointer to stored calibration params.
 * @return float 
 */
float CompassService_GetNormalizedDegressAngle(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibration_params);

/**
 * @brief Calibrate HMC5883L over provided iterations.
 * 
 * @param compass_handler HMC5883L_HandlerTypeDef pointer to module handler.
 * @param compass_calibration_params CompassCalibrationParamsTypeDef pointer to stored calibration params.
 * @param iterations Number of iterations (measures) used for calibration.
 */
void CompassService_HMC5883L_Calibrate(HMC5883L_HandlerTypeDef *compass_handler, CompassCalibrationParamsTypeDef *compass_calibration_params, int iterations);

#endif /* COMPASS_SERVICE_H_ */
