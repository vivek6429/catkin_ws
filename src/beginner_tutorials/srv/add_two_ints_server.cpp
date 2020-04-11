#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"

bool add(beginner_tutorials::AddTwoInts::Request &req,beginner_tutorials::AddTwoInts::Response &res)
{
    res.sum=req.a+req.b;
    ROS_INFO("request: x=%ld , y=%ld",(long int) req.a, (long int) req.b);
    ROS_INFO("Sending back response: [%ld]",(long int) res.sum);
    return true;

}

int main(int argc , char  **argv)
{
    ros::init(argc,argv,"add_two_ints_service_server");
    ros::NodeHandle n;
    ros::ServiceServer ss=n.advertiseService("add_two_ints",add);
    ROS_INFO("Server running");
    ros::spin();
    return 0;

}