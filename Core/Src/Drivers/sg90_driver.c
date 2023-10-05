#include "Drivers/sg90_driver.h"

#include "Services/pwm_service.h"

void SG90Driver_SetPosition(TIM_HandleTypeDef* htim, uint32_t channel, int8_t degrees) {
	if (degrees > 90) degrees = 90;
	if (degrees < -90) degrees = -90;

	float duty_cycle = 0.00000067901 * degrees * degrees + 0.00055 * degrees + 0.09;
    
	PwmService_SetDutyCycle(htim, channel, duty_cycle);
}
