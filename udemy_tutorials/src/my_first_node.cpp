#include <ros/ros.h>

int main(int argc, char **argv)
{
    // în here we init the node with its name
    ros::init(argc, argv, "my_first_cpp_node");

    // we create a NodeHandle object to use the ROS functionalities  
    ros::NodeHandle nh;

    ROS_INFO("Node has been started");
    
    /* we can create a temporary Duration object and use that to sleep the function for a desired amount of time
    ros::Duration(1.0).sleep();
    ROS_INFO("Exit");
    */
    ros::Rate rate{20};
    while(ros::ok()){
        ROS_INFO("here I am published");
        rate.sleep();
    }
}
