
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>

//rosrun mypackage string_converter

ros::Publisher output_pub;
void inputCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Received message: %s", msg->data.c_str());
  std::string upperCaseString = msg->data;
  std::transform(upperCaseString.begin(), upperCaseString.end(), upperCaseString.begin(), ::toupper);
  ROS_INFO("Converted message: %s", upperCaseString.c_str());
  
  std_msgs::String output_msg;
  output_msg.data = upperCaseString;
  output_pub.publish(output_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "string_converter");
  ros::NodeHandle nh;
  
  ros::Subscriber sub = nh.subscribe("input_topic", 1000, inputCallback);
  output_pub = nh.advertise<std_msgs::String>("output_topic", 1000);
 
  ros::spin();
  return 0;
}
