
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <string>



//rosrun mypackage string_converter_test

#include <ros/ros.h>
#include <std_msgs/String.h>
void outputCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  float fDelay = 0;
  ros::init(argc, argv, "string_converter_test");
  ros::NodeHandle n;
  ros::Publisher input_pub = n.advertise<std_msgs::String>("input_topic", 1000);
  ros::Subscriber output_sub = n.subscribe("output_topic", 1000, outputCallback);
  ros::Rate loop_rate(100000);

  while (ros::ok())
  {
    if (fDelay > 0)
    {
    	fDelay--;
    	loop_rate.sleep();
    }
    else
    {
	std_msgs::String msg;
	std::getline(std::cin, msg.data);//getline()在等待用户输入回车符，如果用户没有输入，getline()不会返回，导致阻塞后面的ros::spinOnce()的运行。
	input_pub.publish(msg);
	fDelay = 1000; //发布后，延迟一段时间不要去调用std::cin.peek()，以免被阻塞而无法接收订阅消息（string_converter节点返回的大写字符串）。
    }
    ros::spinOnce(); //当用户没有输入回车时，std::getline()会阻塞，导致运行不到此处，无法接受订阅消息
  }

  return 0;
}




