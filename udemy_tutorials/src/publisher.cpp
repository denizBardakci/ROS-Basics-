#include <ros/ros.h>
#include <std_msgs/String.h>

//http://docs.ros.org/en/indigo/api/roscpp/html/index.html for roscpp API

// 'argc' is the number of variables which gets passed to our C++ node at runtime 
//  and 'argv' is the actual array of values.
int main(int argc, char **argv){
    ros::init(argc, argv, "first_publisher_node");
    ros::NodeHandle node_handle;
    
    /* How to create a Publisher?
    1) publisher object's type is ros::Publisher, and this object is initialized with the return value of advertise function
    2) advertise function is a member function of ros::NodeHandle class. 
       This function is specialized with the message type that we want to publish, in here it is std_msgs::String.
    3) advertise function takes 2 parameters, 1st one is the topic name, i.e. where we will publish the message
        2nd one is the queue size for messages. This size represents how many message can wait in the queue. 
        if the messages in the queue cannot be published, then those messages will be discarded from the queue.
    
    */

    ros::Publisher first_publisher = node_handle.advertise<std_msgs::String>("publisher_topic", 20);
    
    ros::Rate rate{10}; // rate object with value 10Hz, 10 messages per second 
    
    ROS_INFO("publisher node is started");
    int counter{};
    std_msgs::String msg; 
    while(ros::ok()){
       
        msg.data = "Hi this is a published message and its number is: " + std::to_string(counter) + "\n";
        first_publisher.publish(msg);
        counter++;
        rate.sleep(); // we make sure that the while loop operates at the desired frequency. by using sleep function, we put sleep while for a 1/10Hz time duration.

    }
}