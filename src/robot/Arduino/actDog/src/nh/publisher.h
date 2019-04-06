#ifndef INCLUDE_PUBLISHER
#define INCLUDE_PUBLISHER

#include <ros.h>
#include <std_msgs/Int32.h>
#include <Arduino.h>

#define Encoder_UR_Z 21 //2
#define Encoder_UL_Z 20 //3
#define Encoder_DL_Z 19 //4
#define Encoder_DR_Z 18 //5

namespace Enc0{
  int pin=Encoder_UR_Z;
  volatile long zeroCount;

  void resetCb(const std_msgs::Int32&msg){
    zeroCount=0;
  }
  ros::Subscriber<std_msgs::Int32>sub("motor0/reset",&resetCb);

  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor0/zero",&pub_msg);

  void publish(){
    pub.publish(&pub_msg);
  }

  void func(){
    zeroCount++;
  }

  void setup(){
    zeroCount=0;
    nh.advertise(pub);
    pub_msg.data=0;
    attachInterrupt(2,func,FALLING);
  }

  void update(){
    pub_msg.data=zeroCount;
  }
}

namespace Enc1{
  int pin=Encoder_UL_Z;
  volatile long zeroCount;

  void resetCb(const std_msgs::Int32&msg){
    zeroCount=0;
  }
  ros::Subscriber<std_msgs::Int32>sub("motor1/reset",&resetCb);

  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor1/zero",&pub_msg);

  void publish(){
    pub.publish(&pub_msg);
  }

  void func(){
    zeroCount++;
  }

  void setup(){
    zeroCount=0;
    nh.advertise(pub);
    pub_msg.data=0;
    attachInterrupt(2,func,FALLING);
  }

  void update(){
    pub_msg.data=zeroCount;
  }
}
namespace Enc2{
  int pin=Encoder_DL_Z;
  volatile long zeroCount;

  void resetCb(const std_msgs::Int32&msg){
    zeroCount=0;
  }
  ros::Subscriber<std_msgs::Int32>sub("motor2/reset",&resetCb);

  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor2/zero",&pub_msg);

  void publish(){
    pub.publish(&pub_msg);
  }

  void func(){
    zeroCount++;
  }

  void setup(){
    zeroCount=0;
    nh.advertise(pub);
    pub_msg.data=0;
    attachInterrupt(2,func,FALLING);
  }

  void update(){
    pub_msg.data=zeroCount;
  }
}
namespace Enc3{
  int pin=Encoder_DR_Z;
  volatile long zeroCount;

  void resetCb(const std_msgs::Int32&msg){
    zeroCount=0;
  }
  ros::Subscriber<std_msgs::Int32>sub("motor3/reset",&resetCb);

  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor3/zero",&pub_msg);

  void publish(){
    pub.publish(&pub_msg);
  }

  void func(){
    zeroCount++;
  }

  void setup(){
    zeroCount=0;
    nh.advertise(pub);
    pub_msg.data=0;
    attachInterrupt(2,func,FALLING);
  }

  void update(){
    pub_msg.data=zeroCount;
  }
}

void valUpdate(){
  Enc0::update();
  Enc1::update();
  Enc2::update();
  Enc3::update();
}

void publisherSetup(){
  Enc0::setup();
  Enc1::setup();
  Enc2::setup();
  Enc3::setup();
}

void publish(){
  valUpdate();
  Enc0::publish();
  nh.spinOnce();
  Enc1::publish();
  nh.spinOnce();
  Enc2::publish();
  nh.spinOnce();
  Enc3::publish();
}


#endif

