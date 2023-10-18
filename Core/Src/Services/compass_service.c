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
		calibration_params->y_scale = (float) x_var / y_var;
	}
	else
	{
		calibration_params->y_scale = 1.0;
		calibration_params->x_scale = (float) y_var / x_var;
	}
}

float CompassService_GetNormalizedDegressAngle(int16_t x_axis, int16_t y_axis, float magnetic_declination, CompassCalibrationParamsTypeDef *calibration_params)
{
	float x_norm = (x_axis - calibration_params->x_offset) * calibration_params->x_scale;
	float y_norm = (y_axis - calibration_params->y_offset) * calibration_params->y_scale;

	float heading = atan2f(y_norm, x_norm);

	heading += (magnetic_declination > 0 ? magnetic_declination : -magnetic_declination);

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
