#include "ros/ros.h"
#include <string>
//#include "math.h"
#include <geometry_msgs/Vector3.h>
//#include <sstream>
#include <geometry_msgs/Twist.h>
#include <slave_msgs/slave_VelocityID.h>



std::string robot_id;
geometry_msgs::Vector3  robot_linear;
geometry_msgs::Vector3  robot_angular;
geometry_msgs::Twist msg;

void robotControl_callback( slave_msgs::slave_VelocityID msgInput)
{

   robot_id = msgInput.id;
   robot_linear = msgInput.linear;
   robot_angular = msgInput.angular;
   ROS_INFO("The receive control is %s,%f,%f",robot_id.data(), robot_linear.x, robot_angular.z);
   if(robot_id=="1"){//check msg receiver
      
      msg.linear = robot_linear;
      msg.angular = robot_angular;
      ROS_INFO("Successfully");


   } 
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "msg_trans_node");
  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle01/cmd_vel_mux/input/teleop", 1000);
  ros::Subscriber sub1=n.subscribe("/multiKey/cmd_vel", 1000, robotControl_callback);
	
  ros::Rate loop_rate(10);
   //ros::spinOnce();

  int count = 0;
  
  while (ros::ok())
  {
    chatter_pub.publish(msg);
    ROS_INFO("Published");
    ros::spinOnce();
 
    loop_rate.sleep();

    ++count;
  }
 


  return 0;
}

