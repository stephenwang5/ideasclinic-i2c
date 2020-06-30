#ifndef _I2C_HPP_
#define _I2C_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <iostream>
#define I2C_BUS_0 "/dev/i2c-0"
#define I2C_BUS_1 "/dev/i2c-1"

// One instruction for the robotic arm
struct Instruction {
	float x;
	float y;
	float height;
	float width;
	float gripper_angle;
	Instruction();
	Instruction(float, float, float, float, float);
};

// This breaks a floating number into bytes to be sent over I2C
union Converter {
	float argument;
	unsigned char bytes[4];
};

// I2C device character status
enum Status {
	OK,
	Failed_to_open,
	Failed_to_acquire_bus,
	Failed_to_write
};

// Each I2C bus object can be dedicated to a slave
// The bus is only acquired when writing so it doesn't block the file when idling
class I2C_Bus {
	const char* bus;
	unsigned char slave_address;
	Status status;
	void disassemble_float(float, unsigned char*, int);
public:
	I2C_Bus(const char*, unsigned char);
	bool send(Instruction);
};

#endif // _I2C_HPP_
