#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <sstream>
using namespace std;

#define MIN(X,Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))

ros::Publisher dir_pub; // Publisher node of direction message

float newData = 0;
float oldData = 0;
float rL=30,rH=350,oL=65,oH=145;


float mapRange(float val, float rL,float rH,float oL,float oH){
    float outVal;
    outVal = ((oH-oL)/(rH-rL))*(val - rL) + oL;
    return outVal;
}


void tracker_cb (const std_msgs::Float32MultiArray& obj_msg) {
    std_msgs::Float32 dir_val; // Direction value
    

    if (obj_msg.data.size()) {
        newData = obj_msg.data[9];
        ROS_INFO("nD: %f", newData);
        newData = MIN(rH, newData);
        newData = MAX(rL, newData);
        newData = mapRange(newData, rL,rH,oL,oH);
      
        dir_val.data = newData;
        dir_pub.publish(dir_val); // Publish the message
    }

    
}

int main(int argc, char **argv) { 
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;

    ros::Subscriber obj_sub = nh.subscribe("/objects", 1000, tracker_cb);
    dir_pub = nh.advertise<std_msgs::Float32> ("/serv_dir", 1000);
    ros::spin();
    return 0;
}
