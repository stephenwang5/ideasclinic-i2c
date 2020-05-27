
#ifndef _I2C_COMMUNICATION_H_
#define _I2C_COMMUNICATION_H_


// Message definitions
#define I2C_MESSAGE_CONFIRM 0x01
#define I2C_MESSAGE_CONFIRM_SIZEOF 0x01

// Union definition
#include <stdio.h>

union FloatConverter {
	float float_result;
	unsigned char bytes[4];
};

#endif
