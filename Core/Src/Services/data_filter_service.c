/**
 * @file data_filter_service.c
 * @author Mariana Leite
 * @brief 
 * @version 0.1
 * @date 2023-11-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Services/data_filter_service.h"

float DataFilterService_MovingAverage(buffer_t* buffer, float newValue)
{
	if(buffer->size < MAX_BUFFER_SIZE) {
		buffer->data[buffer->size] = newValue;
		buffer->size++;
		buffer->sum += newValue;
	} else {
		float temp[MAX_BUFFER_SIZE - 1];

		buffer->sum -= buffer->data[0];

		memcpy(temp, buffer->data + 1, MAX_BUFFER_SIZE - 1);
		memcpy(buffer->data, temp, MAX_BUFFER_SIZE - 1);

		buffer->data[MAX_BUFFER_SIZE - 1] = newValue;
		buffer->sum += newValue;
	}

	return buffer->sum/buffer->size;
}
