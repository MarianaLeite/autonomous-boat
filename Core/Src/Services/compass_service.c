/**
 * @file compass_service.c
 * @author João Gomes
 * @brief
 * @version 0.1
 * @date 2023-10-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Services/compass_service.h"

void CompassService_InitCalibrationParams(CompassCalibrationParamsTypeDef *calibration_params)
{
	calibration_params->xmin = 32767;
	calibration_params->ymin = 32767;

	calibration_params->xmax = -32768;
	calibration_params->ymax = -32768;

	calibration_params->x_offset = 0;
	calibration_params->y_offset = 0;

	calibration_params->x_scale = 1.0;
	calibration_params->y_scale = 1.0;
}

void CompassService_Calibrate(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibration_params)
{
	int16_t x_var, y_var;

	if (x_axis < calibration_params->xmin) calibration_params->xmin = x_axis;
	if (x_axis > calibration_params->xmax) calibration_params->xmax = x_axis;
	if (y_axis < calibration_params->ymin) calibration_params->ymin = y_axis;
	if (y_axis > calibration_params->ymax) calibration_params->ymax = y_axis;

	calibration_params->x_offset = (calibration_params->xmax + calibration_params->xmin) / 2;
	calibration_params->y_offset = (calibration_params->ymax + calibration_params->ymin) / 2;

	x_var = calibration_params->xmax - calibration_params->xmin;
	y_var = calibration_params->ymax - calibration_params->ymin;

	if (x_var > y_var)
	{
		calibration_params->x_scale = 1.0;
		calibration_params->y_scale = y_var > 0 ? (float) x_var / y_var : 1.0;
	}
	else
	{
		calibration_params->y_scale = 1.0;
		calibration_params->x_scale = x_var > 0 ? (float) y_var / x_var : 1.0;
	}
}

float CompassService_GetNormalizedDegressAngle(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibration_params)
{
	float x_norm = (x_axis - calibration_params->x_offset) * calibration_params->x_scale;
	float y_norm = (y_axis - calibration_params->y_offset) * calibration_params->y_scale;

	float heading = atan2f(y_norm, x_norm);

	heading += MAGNETIC_DECLINATION;

	if (heading < 0)
	{
		heading += 2 * M_PI;
	}
	else if (heading >= 2 * M_PI)
	{
		heading -= 2 * M_PI;
	}

	float degress = heading * 180.00 / M_PI;

	return degress;
}

void CompassService_HMC5883L_Calibrate(HMC5883L_HandlerTypeDef *compass_handler, CompassCalibrationParamsTypeDef *compass_calibration_params, int iterations)
{
	HMC5883L_DataTypeDef compass_data;

	CompassService_InitCalibrationParams(compass_calibration_params);

	for (int i=0; i<iterations; i++)
	{
		HMC5883LDriver_Read(compass_handler, &compass_data, 100);
		CompassService_Calibrate(compass_data.x_axis, compass_data.y_axis, compass_calibration_params);
		HAL_Delay(10);
	}
}
