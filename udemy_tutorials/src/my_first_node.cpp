#include <ros/ros.h>

int main(int argc, char **argv)
{
    // în here we init the node with its name
    ros::init(argc, argv, "my_first_cpp_node");

    // we start the node 
    ros::NodeHandle nh;

    ROS_INFO("Node has been started");
    
    /*duration tanimlayip bu sure boyunca sleep edebiliyoruz
    ros::Duration(1.0).sleep();
    ROS_INFO("Exit");
    */
    ros::Rate rate{20};
    while(ros::ok()){
        ROS_INFO("here I am published");
        // bu loop'un ros::Rate rate objesinin degeri kadar sikliklarla
        // calismasini sagliyoruz, bu durumda saniyede 20 kez, yani 20Hz
        rate.sleep();
    }
}
