#include "i2c.hpp"

Instruction::Instruction() : x(0), y(0), width(0), height(0), gripper_angle(0) {}

Instruction::Instruction(float x, float y, float w, float h, float ga) :
	x(x), y(y), width(w), height(h), gripper_angle(ga) {}

// I2C_Bus::I2CBus() {}

bool I2C_Bus::send(Instruction arg) {
	int file = open(I2C_BUS_0, O_RDWR);
	if (file < 0) {
		printf("Failed to open bus char device\n");
		return false;
	}
	// change the address here
	if (ioctl(file, I2C_SLAVE, 0x1a) < 0) {
		printf("Failed to acquire bus access\n");
		return false;
	}

	char buffer[3] = {'b','b','c'};

	if (write(file, buffer, 3) != 3) {
		printf("Failed to write to bus\n");
		printf("%s\n\n", buffer);
		// return false;
	}
	close(file);
	return true;
}
