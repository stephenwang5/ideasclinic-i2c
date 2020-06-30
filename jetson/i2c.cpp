#include "i2c.hpp"

Instruction::Instruction() : x(0), y(0), width(0), height(0), gripper_angle(0) {}

Instruction::Instruction(float x, float y, float w, float h, float ga) :
	x(x), y(y), width(w), height(h), gripper_angle(ga) {}

I2C_Bus::I2C_Bus(const char* bus, unsigned char unshifted_address) :
	bus(bus), slave_address(unshifted_address) {}

// Helper for turning a float into 4 bytes
void I2C_Bus::disassemble_float(float target, unsigned char* destination, int start) {
	Converter temp;
	temp.argument = target;
	for (int i = 0; i < 4; i++)
		destination[start+i] = temp.bytes[i];
}

bool I2C_Bus::send(Instruction arg) {
	int file = open(bus, O_RDWR);
	if (file < 0) {
		std::cerr << "Failed to open bus char device\n";
		return false;
	}
	if (ioctl(file, I2C_SLAVE, slave_address) < 0) {
		std::cerr << "Failed to acquire bus access\n";
		close(file);
		return false;
	}

	// Change this buffer size to the number of arguments x 4 (for float)
	unsigned char buffer[20];

	disassemble_float(arg.x, buffer, 0);
	disassemble_float(arg.y, buffer, 4);
	disassemble_float(arg.width, buffer, 8);
	disassemble_float(arg.height, buffer, 12);
	disassemble_float(arg.gripper_angle, buffer, 16);

	// Remember to match the size of buffer
	if (write(file, buffer, 20) != 20) {
		std::cerr << "Failed to write to slave\n";
		close(file);
		return false;
	}
	close(file);
	return true;
}
