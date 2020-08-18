#ifndef _I2C_COMMUNICATION_H_
#define _I2C_COMMUNICATION_H_


// Message definitions
// Not yet implemented, to be used when
// numeric replies are required
#define I2C_MESSAGE_CONFIRM 0x01
#define I2C_MESSAGE_CONFIRM_SIZEOF 0x01

// Union definition
#include <stdio.h>
// I2C_HandleTypeDef definition
#include "main.h"

union FloatConverter {
	float float_result;
	unsigned char bytes[4];
};

float fAssembleFloatFromBytes(unsigned char*);
void floats_from_bytes(unsigned char*, float*);
void receive_command(I2C_HandleTypeDef*, float*);

#endif // _I2C_COMMUNICATION_H_
