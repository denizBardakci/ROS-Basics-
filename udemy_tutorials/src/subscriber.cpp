#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>

// typedef boost::shared_ptr<const std_msgs::String > StringConstPtr;
// instead of expecting the data itself, we expect the address of that data. 
// so in here, we use address of the data. we use typedef decleration for std_msgs::String::ConstPtr.

void callBack(const std_msgs::StringConstPtr& msg){
    std::string msg_str = msg->data;
    //Option 1: use iostream library 
    std::cout << msg_str << " ";
    //Option 2: use c_str to convert messaga data to cstring and use ROS_INFO
    //ROS_INFO("%s ", msg_str.c_str());
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "subscriber_node");
    ros::NodeHandle node_handle;
    // subscribe function is member function of ros::NodeHandle class, 
    // we can reach to it via ros::NodeHandle object, i.e. node_handle.

    // subscribe function returns a type of ros::Subscriber. 
    // subscribe method connects to the master to register interest in a given topic. 
    // The node will automatically be connected with publishers on this topic.
     
     // 3 argument, 1) topic that we will subscribe to, 
                //  2) queue size for the incoming message,  
                //     so the queue will hold that amount of messages until messages are processed.
                //  3) function pointer: this function will be called whenever a new message is recieved.
                //     we can use function name directly here because implicitly, function names are converted to function pointers.
                //     OR we can take address of function and pass it as argument as well, like &callBack.

    ros::Subscriber my_sub_object = node_handle.subscribe("publisher_topic", 10, callBack);
    
    
    //This function will not return until the node has been shut down, which means it will keep our main function running which has our subscriber callback running.
    ros::spin(); 
    
}