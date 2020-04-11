#include <ros/ros.h>
#include "husky_2/HuskyHighlevelController.hpp"

int main(int argc, char **argv) {
	//the following step must be done before initializing node handler
	ros::init(argc, argv, "husky_2");

	// create a private namespace nodeHandle---an access point to all communication in ros
	ros::NodeHandle nodeHandle("~");
	husky_controller_namespace::Husky_2 Husky_2(nodeHandle);

	ros::spin();
	return 0;
}

