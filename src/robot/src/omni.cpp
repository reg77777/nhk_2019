#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Pose.h>

#ifndef M_PI
#define M_PI 3.1415926535897932
#endif

#define UP_RIGHT    0
#define DOWN_RIGHT  1
#define DOWN_LEFT   2
#define UP_LEFT     3

class Omni {
    
    public:
        Omni();
    
    private:
        void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

        ros::NodeHandle nh;

        ros::Publisher motor_pub[4];
};


Omni::Omni() {

    motor_pub[UP_RIGHT]   =  nh.advertise<std_msgs::Float32>("/motor_upright",1);
    motor_pub[DOWN_RIGHT] =  nh.advertise<std_msgs::Float32>("/motor_downpright",1);
    motor_pub[DOWN_LEFT]  =  nh.advertise<std_msgs::Float32>("/motor_downleft",1);
    motor_pub[UP_LEFT]    =  nh.advertise<std_msgs::Float32>("/motor_upleft",1);

}


int main(int argc,char ** argv){
    ros::init(argc,argv,"omni");
    Omni omni();
    ros::spin();
    return 0;
}
