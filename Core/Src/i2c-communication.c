#include "i2c-communication.h"
#include <string.h>

float fAssembleFloatFromBytes(unsigned char *byte_data) {
	union FloatConverter converter;

	for (int arr_idx = 0; arr_idx < 4; arr_idx++) {
		converter.bytes[arr_idx] = byte_data[arr_idx];
	}

	return converter.float_result;
}

void floats_from_bytes(unsigned char* bytes, float* destination) {
	for (int i = 0; i < strlen((char*)bytes); i+=4)
		destination[i/4] = fAssembleFloatFromBytes(bytes+i);
}

void receive_command(I2C_HandleTypeDef* handle, float* destination) {
	// the size of buffer "data" received from the i2c bus should be
	// the same as the buffer size on the jetson (4x # of floats)
	uint8_t bytes_buffer[20];
	HAL_I2C_Slave_Receive(handle, bytes_buffer, 20, HAL_MAX_DELAY);
	floats_from_bytes(bytes_buffer, destination);
}
