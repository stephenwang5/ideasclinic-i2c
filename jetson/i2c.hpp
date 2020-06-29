#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <iostream>
#define I2C_BUS_0 "/dev/i2c-0"
#define I2C_BUS_1 "/dev/i2c-1"

struct Instruction {
	float x;
	float y;
	float height;
	float width;
	float gripper_angle;
	Instruction();
	Instruction(float, float, float, float, float);
};

class I2C_Bus {
public:
	// I2C_Bus();
	bool send(Instruction);
};
