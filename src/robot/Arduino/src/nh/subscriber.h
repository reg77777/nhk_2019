#ifndef INCLUDE_SUBSCRIBER
#define INCLUDE_SUBSCRIBER

#include <stdio.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include "nh.h"
#include "../motor/motor.h"

#define MOTOR_UR_CW  2
#define MOTOR_UR_CCW 3
#define MOTOR_DR_CW  4
#define MOTOR_DR_CCW 5
#define MOTOR_DL_CW  6
#define MOTOR_DL_CCW 7
#define MOTOR_UL_CW  9
#define MOTOR_UL_CCW 10

namespace Motor0{
  struct MotorPins pins = {MOTOR_UR_CW,MOTOR_UR_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    printf("%d",msg.data);
    nh.loginfo("motor0");
  }
  const char * topic_name= "moto_0";
  ros::Subscriber<std_msgs::Float32>sub(topic_name,&callback);

}

namespace Motor1{
  struct MotorPins pins = {MOTOR_DR_CW,MOTOR_DR_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    printf("%d",msg.data);
    nh.loginfo("motor1");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor1",&callback);
}

namespace Motor2{
  struct MotorPins pins = {MOTOR_DL_CW,MOTOR_DL_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    printf("%d",msg.data);
    nh.loginfo("motor2");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor2",&callback);
}

namespace Motor3{
  struct MotorPins pins = {MOTOR_UL_CW,MOTOR_UL_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    nh.loginfo("motor3");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor3",&callback);
} 
namespace All{
  void callback(const std_msgs::Float32 &msg){
    nh.loginfo("All_stop");
  }
  ros::Subscriber<std_msgs::Float32>sub("all",&callback);
}

void setSubscriber(){
  nh.subscribe(Motor0::sub);
  nh.subscribe(Motor1::sub);
  nh.subscribe(Motor2::sub);
  nh.subscribe(Motor3::sub);
}

#endif
