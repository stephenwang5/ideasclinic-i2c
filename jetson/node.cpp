#include "ros/ros.h"
#include "ros/console.h"
#include "i2c.hpp"
#include "i2c/i2c_write.h"

class Robot_Arm_I2C {
    I2C_Bus device;
    Instruction command;
    ros::Subscriber sub;
    void bus_write_callback(const i2c::i2c_write& arg) {
        command.x = arg.x;
        command.y = arg.y;
        command.height = arg.height;
        command.width = arg.width;
        command.gripper_angle = arg.gripper_angle;
        if (!device.send(command))
            ROS_DEBUG("Failed to send to robot arm via I2C");
    }
public:
    Robot_Arm_I2C(ros::NodeHandle& ros_handle) : device(I2C_BUS_0, 0x1a), command() {
        sub = ros_handle.subscribe("/robot_arm_i2c", 10, &Robot_Arm_I2C::bus_write_callback, this);
    }
};

int main (int argc, char** argv) {

    ros::init(argc, argv, "i2c_node");
    ros::NodeHandle h;

    Robot_Arm_I2C obj(h);

    ros::spin();

	return 0;
}
