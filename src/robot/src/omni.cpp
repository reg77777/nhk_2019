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

        ros::Subscriber omni_sub;
        ros::Subscriber joy_sub;

        ros::Subscriber enc_sub[4];
        ros::Subscriber current_sub[4];
        ros::Subscriber volt_sub[4];
        ros::Subscriber therm_sub[4];

//sensor values
        float enc[4];
        float current[4];
        float volt[4];
        float therm[4];

//params
        float dt;
        float max_accel;
        float tire_diameter[4]; 
        float enc_reso[4];      //encoder resolution

//pose

};


Omni::Omni() {

    motor_pub[UP_RIGHT]   =  nh.advertise<std_msgs::Float32>("/motor_upright",1);
    motor_pub[DOWN_RIGHT] =  nh.advertise<std_msgs::Float32>("/motor_downpright",1);
    motor_pub[DOWN_LEFT]  =  nh.advertise<std_msgs::Float32>("/motor_downleft",1);
    motor_pub[UP_LEFT]    =  nh.advertise<std_msgs::Float32>("/motor_upleft",1);


    //omni_sub              =  nh.subscribe<std_msgs::> //TODO How msg is adequate ?
    
    joy_sub               =  nh.subscribe<sensor_msgs::Joy>("/joy",10,&Omni::joyCallback,this);  

//init sensor value  
    for(int i=0;i<4;i++){
        enc[i]    =  0.0f;
        current[i]    =  0.0f;
        volt[i]    =  0.0f;
        therm[i] =  0.0f;
    }
}

void Omni::joyCallback(const sensor_msgs::Joy::ConstPtr& sub_msg){
}


int main(int argc,char ** argv){
    ros::init(argc,argv,"omni");
    Omni omni();
    ros::spin();
    return 0;
}
