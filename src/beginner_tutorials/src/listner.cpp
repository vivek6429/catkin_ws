#include "ros/ros.h"
#include "std_msgs/String.h"
using namespace std;



void chatterCallBack(const std_msgs::String::ConstPtr& msg)
{
 ROS_INFO("I heared :[%s]",msg->data.c_str());
 ROS_INFO_STREAM("I heard: "<< (msg->data.c_str()));}

int main(int argc,char **argv){

    ros::init(argc,argv,"listener");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatter_topic", 1000, chatterCallBack);
    ros::spin();

    return 0;
}