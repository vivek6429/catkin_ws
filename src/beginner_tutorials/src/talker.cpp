#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc,char **argv)
{
    ros::init(argc,argv,"talker_node");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<std_msgs::String>("chatter_topic",1000);
    ros::Rate loop_rate(10);

    int counter=0;
    while (ros::ok())
    {   std_msgs::String msg;
        std::stringstream ss;
        ss<<"hello count====="<<counter;
        msg.data=ss.str();
        ROS_INFO_STREAM("hello count====="<<counter);
        ROS_INFO("%s", msg.data.c_str());        
        pub.publish(msg);
        counter++;
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}