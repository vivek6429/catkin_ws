#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "tf/message_filter.h"
#include "message_filters/subscriber.h"

class PoseDrawer
{
public:
  PoseDrawer() : tf_(),  target_frame_("/turtle1")
  {
    point_sub_.subscribe(n_, "turtle_point_stamped", 10);
    tf_filter_ = new tf::MessageFilter<geometry_msgs::PointStamped>(point_sub_, tf_, target_frame_, 10);
    tf_filter_->registerCallback( boost::bind(&PoseDrawer::msgCallback, this, _1) );
  } ;

private:
  message_filters::Subscriber<geometry_msgs::PointStamped> point_sub_;
  tf::TransformListener tf_;
  tf::MessageFilter<geometry_msgs::PointStamped> * tf_filter_;
  ros::NodeHandle n_;
  std::string target_frame_;

  //  Callback to register with tf::MessageFilter to be called when transforms are available
  void msgCallback(const boost::shared_ptr<const geometry_msgs::PointStamped>& point_ptr) 
  {
    geometry_msgs::PointStamped point_out;
    try 
    {
      tf_.transformPoint(target_frame_, *point_ptr, point_out);
      
      printf("point of turtle 3 in frame of turtle 1 Position(x:%f y:%f z:%f)\n", 
             point_out.point.x,
             point_out.point.y,
             point_out.point.z);
    }
    catch (tf::TransformException &ex) 
    {
      printf ("Failure %s\n", ex.what()); //Print exception which was caught
    }
  };

};


int main(int argc, char ** argv)
{
  ros::init(argc, argv, "pose_drawer"); //Init ROS
  PoseDrawer pd; //Construct class
  ros::spin(); // Run until interupted 
};
// #include <ros/ros.h>
// #include <tf/transform_listener.h>
// #include <geometry_msgs/Twist.h>
// #include <turtlesim/Spawn.h>

// int main(int argc, char** argv){
//   ros::init(argc, argv, "my_tf_listener");

//   ros::NodeHandle node;

//   ros::service::waitForService("spawn");
//   ros::ServiceClient add_turtle =
//     node.serviceClient<turtlesim::Spawn>("spawn");
//   turtlesim::Spawn srv;
//   add_turtle.call(srv);

//   ros::Publisher turtle_vel =node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

//   tf::TransformListener listener;

//   ros::Rate rate(10.0);
//   while (node.ok()){
//     tf::StampedTransform transform;
//     try{
//       listener.lookupTransform("/turtle2", "/turtle1",
//                                ros::Time(0), transform);
//     }
//     catch (tf::TransformException &ex) {
//       ROS_ERROR("%s",ex.what());
//       ros::Duration(1.0).sleep();
//       continue;
//     }

//     geometry_msgs::Twist vel_msg;
//     vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),
//                                     transform.getOrigin().x());
//     vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) +
//                                   pow(transform.getOrigin().y(), 2));
//     turtle_vel.publish(vel_msg);

//     rate.sleep();
//   }
//   return 0;
// };