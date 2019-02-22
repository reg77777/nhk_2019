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


namespace MotorUpRight{
  struct MotorPins pins = {MOTOR_UR_CW,MOTOR_UR_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    printf("%d",msg.data);
    nh.loginfo("up_right");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor_ur_sub",&callback);

}

namespace MotorUpLeft{
  struct MotorPins pins = {MOTOR_DR_CW,MOTOR_DR_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    printf("%d",msg.data);
    nh.loginfo("up_left");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor_ul_sub",&callback);
}

namespace MotorDownLeft{
  struct MotorPins pins = {MOTOR_DL_CW,MOTOR_DL_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    printf("%d",msg.data);
    nh.loginfo("down_left");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor_dl_sub",&callback);
}

namespace MotorDownRight{
  struct MotorPins pins = {MOTOR_UL_CW,MOTOR_UL_CCW};
  Motor motor(pins);

  void callback(const std_msgs::Float32 &msg){
    motor.run(msg.data);
    nh.loginfo("down_right");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor_dr_sub",&callback);
}

namespace All{
  void callback(const std_msgs::Float32 &msg){
    nh.loginfo("All_stop");
  }
  ros::Subscriber<std_msgs::Float32>sub("motor_dr_sub",&callback);
}

void setSubscriber(){
  nh.subscribe(MotorUpRight::sub);
  nh.subscribe(MotorUpLeft::sub);
  nh.subscribe(MotorDownLeft::sub);
  nh.subscribe(MotorDownRight::sub);
}

#endif
