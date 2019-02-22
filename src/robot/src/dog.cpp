/*
 * this is the program about actuator;
*/

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>

#define     RIGHT_FORE     0
#define     LEFT_FORE      1
#define     RIGHT_HIND     2
#define     LEFT_HIND      3
#define     LEG_QTY        4

class Dog {
    
    public:
        Dog();

    private:
        ros::NodeHandle nh;

        ros::Subscriber walk_sub;
        void callback(const std_msgs::Float32::ConstPtr& sub_msg);

        ros::Subscriber motorcon_sub[LEG_QTY];
        void motorcon_callback0(const std_msgs::Float32::ConstPtr& sub_msg); 
        void motorcon_callback1(const std_msgs::Float32::ConstPtr& sub_msg); 
        void motorcon_callback2(const std_msgs::Float32::ConstPtr& sub_msg); 
        void motorcon_callback3(const std_msgs::Float32::ConstPtr& sub_msg); 
        void motorcon(int which,float data);

        ros::Subscriber enc_sub[LEG_QTY];
        void enc_callback0(const std_msgs::Float32::ConstPtr& sub_msg);
        void enc_callback1(const std_msgs::Float32::ConstPtr& sub_msg);
        void enc_callback2(const std_msgs::Float32::ConstPtr& sub_msg);
        void enc_callback3(const std_msgs::Float32::ConstPtr& sub_msg);

        ros::Publisher  motor_pub[LEG_QTY];
        ros::Publisher  air_pub[LEG_QTY];

        float enc_dt[LEG_QTY];
        float enc[LEG_QTY];
        float wheelspeed[LEG_QTY];
        
        float kp;
        float ki;
        float kd;

};

Dog::Dog() {

   kp = 1.0; //後で何とかする
   ki = 0; //後で何とかする
   kd = 0; //後で何とかする

   motor_pub[RIGHT_FORE]= nh.advertise<std_msgs::Float32>("motor0",1);
   motor_pub[LEFT_FORE] = nh.advertise<std_msgs::Float32>("motor1",1);  
   motor_pub[RIGHT_HIND]= nh.advertise<std_msgs::Float32>("motor2",1);
   motor_pub[LEFT_HIND] = nh.advertise<std_msgs::Float32>("motor3",1);

   motorcon_sub[RIGHT_FORE]= nh.subscribe<std_msgs::Float32>("motorcon0",10,&Dog::motorcon_callback0,this);
   motorcon_sub[LEFT_FORE] = nh.subscribe<std_msgs::Float32>("motorcon1",10,&Dog::motorcon_callback1,this);  
   motorcon_sub[RIGHT_HIND]= nh.subscribe<std_msgs::Float32>("motorcon2",10,&Dog::motorcon_callback2,this);
   motorcon_sub[LEFT_HIND] = nh.subscribe<std_msgs::Float32>("motorcon3",10,&Dog::motorcon_callback3,this);

   air_pub[RIGHT_FORE]= nh.advertise<std_msgs::Bool>("air0",1);
   air_pub[LEFT_FORE] = nh.advertise<std_msgs::Bool>("air1",1);
   air_pub[RIGHT_HIND]= nh.advertise<std_msgs::Bool>("air2",1);
   air_pub[LEFT_HIND] = nh.advertise<std_msgs::Bool>("air3",1);

   enc_sub[RIGHT_FORE]= nh.subscribe<std_msgs::Float32>("enc0",10,&Dog::enc_callback0,this);
   enc_sub[LEFT_FORE] = nh.subscribe<std_msgs::Float32>("enc1",10,&Dog::enc_callback1,this);
   enc_sub[RIGHT_HIND]= nh.subscribe<std_msgs::Float32>("enc2",10,&Dog::enc_callback2,this);
   enc_sub[LEFT_HIND] = nh.subscribe<std_msgs::Float32>("enc3",10,&Dog::enc_callback3,this);

}

void Dog::callback(const std_msgs::Float32::ConstPtr& sub_msg){

}

void Dog::motorcon_callback0(const std_msgs::Float32::ConstPtr& sub_msg){
   motorcon(0,sub_msg->data);
}

void Dog::motorcon_callback1(const std_msgs::Float32::ConstPtr& sub_msg){
   motorcon(1,sub_msg->data);
}

void Dog::motorcon_callback2(const std_msgs::Float32::ConstPtr& sub_msg){
   motorcon(2,sub_msg->data);
}

void Dog::motorcon_callback3(const std_msgs::Float32::ConstPtr& sub_msg){
   motorcon(3,sub_msg->data);
}

void Dog::motorcon(int which,float data){
   std_msgs::Float32 msg;
   msg.data = kp*(data-wheelspeed[which]);
   motor_pub[which].publish(msg);
}

void Dog::enc_callback0(const std_msgs::Float32::ConstPtr& sub_msg){
   wheelspeed[RIGHT_FORE] = (sub_msg->data - enc[RIGHT_FORE])/enc_dt[RIGHT_FORE];
   enc[RIGHT_FORE] = sub_msg->data;
}

void Dog::enc_callback1(const std_msgs::Float32::ConstPtr& sub_msg){
   wheelspeed[LEFT_FORE] = (sub_msg->data - enc[RIGHT_FORE])/enc_dt[LEFT_FORE];
   enc[LEFT_FORE] = sub_msg->data;
}

void Dog::enc_callback2(const std_msgs::Float32::ConstPtr& sub_msg){
   wheelspeed[RIGHT_HIND] = (sub_msg->data - enc[LEFT_HIND])/enc_dt[RIGHT_HIND];
   enc[RIGHT_HIND] = sub_msg->data;
}

void Dog::enc_callback3(const std_msgs::Float32::ConstPtr& sub_msg){
   wheelspeed[LEFT_HIND] = (sub_msg->data - enc[LEFT_FORE])/enc_dt[LEFT_HIND];
   enc[LEFT_FORE] = sub_msg->data;
}

int main(int argc,char ** argv){
   ros::init(argc,argv,"dog");
   Dog dog;
   ros::spin();
   return 0;
}
