#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <cstdlib>

int main(int argc ,char **argv)
{
    ros::init(argc,argv,"add_two_int_client");
    if (argc!=3)
    {
        ROS_INFO_STREAM("incorrect usge of args");
        return 1;
        /* code */
    }
    
    ros::NodeHandle nh;
    ros::ServiceClient sc= nh.serviceClient<beginner_tutorials::AddTwoInts>("add_two_ints");
    beginner_tutorials::AddTwoInts srv;
    ROS_INFO_STREAM("arg 0="<<argv[0]);
    srv.request.a=atoll(argv[1]);
    srv.request.b=atoll(argv[2]);

    if(sc.call(srv))
    {
        ROS_INFO("sum: %ld",(long int)srv.response.sum);}
    else 
    {ROS_ERROR("Failed to get response from add_two_ints_service_server");
    return 1;
    }
}