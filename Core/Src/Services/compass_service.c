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
#include "Drivers/hmc5883l_driver.h"
#include "Services/data_filter_service.h"

HMC5883L_HandlerTypeDef magnetometerHandler;
CompassCalibrationParamsTypeDef calibrationParams;

buffer_t xBuffer;
buffer_t yBuffer;

float angle;

void CompassService_Init(I2C_HandleTypeDef* hi2c, TIM_HandleTypeDef* htim)
{
	magnetometerHandler.hi2c = hi2c;
	magnetometerHandler.samples_avg = HMC5883L_8_SAMPLES_AVG;
	magnetometerHandler.output_rate = HMC5883L_OUTPUT_RATE_75_HZ;
	magnetometerHandler.measurement_mode = HMC5883L_MEASUREMENT_MODE_NORMAL;
	magnetometerHandler.gain = HMC5883L_GAIN_4_7_GA;
	magnetometerHandler.i2c_speed = HMC5883L_I2C_NORMAL_SPEED;
	magnetometerHandler.operation_mode = HMC5883L_CONTINUOUS_MEASUREMENT_MODE;

	HMC5883LDriver_Init(&magnetometerHandler, 100);

	calibrationParams.x_offset = 24;
	calibrationParams.y_offset = 14;
	calibrationParams.x_scale = 1.0;
	calibrationParams.y_scale = (float)138/135;

	DataFilterService_InitBuffer(&xBuffer);
	DataFilterService_InitBuffer(&yBuffer);

	HAL_TIM_Base_Start_IT(htim);
}

void CompassService_Calibrate(int iterations)
{
	HMC5883L_DataTypeDef data;

	CompassService_InitCalibrationParams(&calibrationParams);

	for (int i = 0; i < iterations; i++) {
		if(HMC5883LDriver_Read(&magnetometerHandler, &data, 100)) {
			CompassService_UpdateCalibrationParams(data.x_axis, data.y_axis, &calibrationParams);
			HAL_Delay(10);
		}
	}
}

void CompassService_InitCalibrationParams(CompassCalibrationParamsTypeDef *calibrationParams)
{
	calibrationParams->xmin = 32767;
	calibrationParams->ymin = 32767;

	calibrationParams->xmax = -32768;
	calibrationParams->ymax = -32768;

	calibrationParams->x_offset = 0;
	calibrationParams->y_offset = 0;

	calibrationParams->x_scale = 1.0;
	calibrationParams->y_scale = 1.0;
}

void CompassService_UpdateCalibrationParams(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibrationParams)
{
	int16_t x_var, y_var;

	if (x_axis < calibrationParams->xmin) calibrationParams->xmin = x_axis;
	if (x_axis > calibrationParams->xmax) calibrationParams->xmax = x_axis;
	if (y_axis < calibrationParams->ymin) calibrationParams->ymin = y_axis;
	if (y_axis > calibrationParams->ymax) calibrationParams->ymax = y_axis;

	calibrationParams->x_offset = (calibrationParams->xmax + calibrationParams->xmin) / 2;
	calibrationParams->y_offset = (calibrationParams->ymax + calibrationParams->ymin) / 2;

	x_var = calibrationParams->xmax - calibrationParams->xmin;
	y_var = calibrationParams->ymax - calibrationParams->ymin;

	if (x_var > y_var)
	{
		calibrationParams->x_scale = 1.0;
		calibrationParams->y_scale = y_var > 0 ? (float) x_var / y_var : 1.0;
	}
	else
	{
		calibrationParams->y_scale = 1.0;
		calibrationParams->x_scale = x_var > 0 ? (float) y_var / x_var : 1.0;
	}
}

float CompassService_CalculateAngle(int16_t x_axis, int16_t y_axis, CompassCalibrationParamsTypeDef *calibrationParams)
{
	float x_norm = (x_axis - calibrationParams->x_offset) * calibrationParams->x_scale;
	float y_norm = (y_axis - calibrationParams->y_offset) * calibrationParams->y_scale;

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

void CompassService_UpdateCompassAngle()
{
	HMC5883L_DataTypeDef data;
	if(HMC5883LDriver_Read(&magnetometerHandler, &data, 100)) {
		float x = DataFilterService_MovingAverage(&xBuffer, data.x_axis);
		float y = DataFilterService_MovingAverage(&yBuffer, data.y_axis);
		angle = CompassService_CalculateAngle(x, y, &calibrationParams);
	}
}

float CompassService_GetCompassAngle()
{
	return angle;
}
