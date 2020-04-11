#include <ros/ros.h>
#include "husky_2/HuskyHighlevelController.hpp"

namespace husky_controller_namespace {

Husky_2::Husky_2(ros::NodeHandle& nodeHandle) :nodeHandle_(nodeHandle){


	if (!(nodeHandle.getParam("scan_topic_name", topic_name_)
			& nodeHandle.getParam("scan_topic_queue_size", topic_size_queue_))) {
		ROS_ERROR("Could not read parame ters.");

	//	ROS_INFO("Setting parameters fallback.");
	//	topic_name_ = "/scan";
		//topic_size_queue_ = 1;

	}


	ROS_INFO_STREAM("print parameters"<<topic_name_<<"\n"<<topic_size_queue_);
	// create a subscriber to the topic_name
	subscriber_ = nodeHandle_.subscribe(topic_name_, topic_size_queue_,
			&Husky_2::scanCallback, this);
	ROS_INFO("Successfully launched node.");

}

Husky_2::~Husky_2() {
}

void Husky_2::scanCallback(const sensor_msgs::LaserScan& msg) {
	// search for the min value in the vector of msg.ranges
	std::vector<float> ranges = msg.ranges;
	float small = ranges[0];
	for (float v : ranges) {
		ROS_INFO_STREAM("value=: " + std::to_string(v) + "  ");
		if (small > v) {
			small = v;
		}
	}

	// display the ming value
	ROS_INFO_STREAM("Min range: " + std::to_string(small));

}
}
