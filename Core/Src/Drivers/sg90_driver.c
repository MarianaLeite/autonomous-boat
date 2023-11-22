#include "Drivers/sg90_driver.h"

#include "Services/pwm_service.h"

int lastDegrees = 91;

void SG90Driver_SetPosition(TIM_HandleTypeDef* htim, uint32_t channel, int16_t degrees) {
	if (degrees > 90) degrees = 90;
	if (degrees < -90) degrees = -90;

	if (lastDegrees == degrees) return;
	lastDegrees = degrees;

	float duty_cycle = 0.00000004321 * degrees * degrees + 0.000497222 * degrees + 0.0864;
    
	PwmService_SetDutyCycle(htim, channel, duty_cycle);
}
