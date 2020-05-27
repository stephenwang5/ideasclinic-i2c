#include "i2c-communication.h"

float fAssembleFloatFromBytes(unsigned char *byte_data) {
	union FloatConverter converter;

	for (int arr_idx = 0; arr_idx < 4; arr_idx++) {
		converter.bytes[arr_idx] = byte_data[arr_idx];
	}

	return converter.float_result;
};
