#include <ros/ros.h>
#include <std_msgs/String.h>

//http://docs.ros.org/en/indigo/api/roscpp/html/index.html for roscpp API

// 'argc' is the number of variables which gets passed to our C++ node at runtime 
//  and 'argv' is the actual array of values.
int main(int argc, char **argv){
    ros::init(argc, argv, "first_publisher_node");
    ros::NodeHandle node_handle;
    
    // 1) ros::Publisher turunden bir nesne yarattik ve buna ilk degerini bizim node_handle
    // nesnesi icin cagrilmis advertise fonksiyonun geri donus degeri olan 
    // Publisher ile verdik

    // 2) advertise fonksiyonunu yazarken <> icine topic'e gecilecek mesajin turunu yaziyoruz
    // 3) advertise'in argumanlari topic ismi, topic'de kac mesajin queue veri yapisinda publish edilene kadar tutulacagini
    //      bildiriyoruz ama burda queue dolarsa ve pusblish edilmezse queue bosaltilip yeni mesajlar queue'ya ekleniyor

    ros::Publisher first_publisher = node_handle.advertise<std_msgs::String>("publisher_topic", 20);
    
    ros::Rate rate{10}; // rate object with value 10Hz, 10 messages per second yani
    
    ROS_INFO("publisher node is started");
    int counter{};
     std_msgs::String msg; // neden her loop'ta yeni nesne yarattiriyor anlamadim ama farkedersen duzelt bunu.
    while(ros::ok()){
       
        msg.data = "Hi this is a published message and its number is: " + std::to_string(counter);
        first_publisher.publish(msg);
        counter++;
        rate.sleep(); // while loop'unun bizim istedigimiz frekans hizinda calismasini sagliyor

    }
}