#include "ros/ros.h"
#include "i2c.hpp"

int main (int argc, char** argv) {

	I2C_Bus device;
	Instruction command;
    ros::init(argc, argv, "i2c_node");
    ros::NodeHandle h;
    ros::Duration huh(.1);
    for (int i = 0; i < 5; i++) {
	    printf("%d\n", device.send(command));
        huh.sleep();
    }

	return 0;
}
