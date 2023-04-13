#include <ros/ros.h>
#include <std_msgs/String.h>

void outputCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "string_converter_test");
  ros::NodeHandle n;
  ros::Publisher input_pub = n.advertise<std_msgs::String>("input_topic", 1000);
  ros::Subscriber output_sub = n.subscribe("output_topic", 1000, outputCallback);
  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    std_msgs::String msg;
    std::getline(std::cin, msg.data);
    input_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

