#include "ros/ros.h"

#include "std_msgs/Float32.h"

//const float WHEEL_RADIUS = 12.5 / 100; // Size in centimeters --> meters
float WHEEL_RADIUS; // here we will init this value by using rosparam features

ros::Publisher speed_pub;


void subCallback(const std_msgs::Float32::ConstPtr& rpm)
{
  ros::NodeHandle callback_node_handle; 
  // we created another nodehandle object to use ROS features in this function.
  // The reason why we created the nodehandle here is that, we cannot create a nodehandle object before ros::init() function call is completed.
  // since ros::init is in the main, we cannot create a node handle in global namespace, if we do that we get syntax error message. 
  // Because in that case we attempted to create node handle before ros::init func call.
  
  /* --------- Some info about rosparam features------------------------------
   by using getParam function, we search for wheel_radius param on rosparam list, if we found the parameter, we init it with WHEEL_RADIUS variable and use it.
   we can create wheel_radius parameter by rosparam set /wheel_radius 0.1 
   after that we can save the existing parameters to a file (in here we name it params) by doing rosparam dump params.yaml, you have to do that to save the current parameter server information into a file.
   you can create this file in your project folder or in any other place. 

   if you make changes on the params.yaml file, even this file is on project directory and even though you build the project, this does not apply the change. 
   You have to do: rosparam load params.yaml on the terminal.

   To delete the parameter from parameter server, you need to do: rosparam delete \wheel_radius. 
   That means deleting the param from param.yaml does not work. You need to delete the param from terminal or in the code.
  */ 
  if(callback_node_handle.getParam("wheel_radius", WHEEL_RADIUS)){
     std_msgs::Float32 speed_msg;

  // Speed = Circumference * Rev/s
     speed_msg.data = (2 * WHEEL_RADIUS * 3.14159) * (rpm->data / 60);

    speed_pub.publish(speed_msg);  
    //  when the subCallBack is called, here we publish the calculated speed value 
    //  we created the Publisher object in global namespace, by doing that we can directly use it in the local scope of subCallBack function
  
    ROS_INFO("current speed is %f m/s", speed_msg.data);
  }
  else {
    ROS_WARN("wheel_radius parameter is not set\n");
  }
 
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "speed_calc_node");

  ros::NodeHandle node_handle;

  speed_pub = node_handle.advertise<std_msgs::Float32>("speed", 10);

  ros::Subscriber rpm_sub = node_handle.subscribe("rpm", 10, subCallback);

  ros::spin();

  return 0;
}
