#ifndef INCLUDE_PUBLISHER
#define INCLUDE_PUBLISHER

#include <ros.h>
#include <Arduino.h>
#include <std_msgs/Int32.h>

// 21 20 19 18
#define Encoder_UR_A 21 //interrupt 2
#define Encoder_UR_B 25 
#define Encoder_UL_A 20 //interrupt 3
#define Encoder_UL_B 24 
#define Encoder_DL_A 19 //interrupt 3
#define Encoder_DL_B 23 
#define Encoder_DR_A 18 //interrupt 5
#define Encoder_DR_B 22 

struct EncoderPins{
  int A;
  int B;
  void setup(){
    pinMode(A,INPUT);
    pinMode(B,INPUT);
  };
};

namespace Enc0{
  struct EncoderPins 
    pins = {Encoder_UR_A,Encoder_UR_B};
  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor0/enc",&pub_msg);
  void publish(){
    pub.publish(&pub_msg); 
  }

  volatile int oldB;
  volatile long encValue;
  void func(){
    int newB = digitalRead(Encoder_UR_B);
    int newA = digitalRead(Encoder_UR_A);

    if (newA){
      if (oldB && !newB) { // up
        ++encValue;
      } else { // down
        --encValue;
      }
    } else {
      if (oldB && !newB) { // down
        --encValue;
      } else { // up
        ++encValue;
      }
    } oldB = newB;
  }
  void setup(){
    oldB=0;
    encValue=0;
    nh.advertise(pub);
    pins.setup();
    attachInterrupt(2,func,CHANGE);
    pub_msg.data=0;
  }
  void update(){
    pub_msg.data = encValue;
  }
}

namespace Enc1{
  struct EncoderPins 
    pins = {Encoder_DR_A,Encoder_DR_B};
  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor1/enc",&pub_msg);
  void publish(){
    pub.publish(&pub_msg); 
  }

  volatile int oldB;
  volatile long encValue;
  void func(){
    int newB = digitalRead(Encoder_UL_B);
    int newA = digitalRead(Encoder_UL_A);

    if (newA){
      if (oldB && !newB) { // up
        ++encValue;
      } else { // down
        --encValue;
      }
    } else {
      if (oldB && !newB) { // down
        --encValue;
      } else { // up
        ++encValue;
      }
    }
    oldB = newB;
  }
  void setup(){
    oldB=0;
    encValue=0;
    nh.advertise(pub);
    pins.setup();
    attachInterrupt(3,func,CHANGE);
    pub_msg.data=0;
  }
  void update(){
    pub_msg.data = encValue;
  }
}

namespace Enc2{
  struct EncoderPins 
    pins = {Encoder_DL_A,Encoder_DL_B};
  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor2/enc",&pub_msg);
  void publish(){
    pub.publish(&pub_msg); 
  }

  volatile int oldB;
  volatile long encValue;

  void func(){
    int newB = digitalRead(Encoder_DL_B);
    int newA = digitalRead(Encoder_DL_A);

    if (newA){
      if (oldB && !newB) { // up
        ++encValue;
      } else { // down
        --encValue;
      }
    } else {
      if (oldB && !newB) { // down
        --encValue;
      } else { // up
        ++encValue;
      }
    }
    oldB = newB;
  }
  void setup(){
    oldB=0;
    encValue=0;
    nh.advertise(pub);
    pins.setup();
    attachInterrupt(4,func,CHANGE);
    pub_msg.data=0;
  }
  void update(){
    pub_msg.data = encValue;
  }
}

namespace Enc3{
  struct EncoderPins 
    pins = {Encoder_UL_A,Encoder_UL_B};
  std_msgs::Int32 pub_msg;
  ros::Publisher pub("motor3/enc",&pub_msg);
  void publish(){
    pub.publish(&pub_msg); 
  }

  volatile int oldB;
  volatile long encValue;
  void func(){
    int newB = digitalRead(Encoder_DR_B);
    int newA = digitalRead(Encoder_DR_A);

    if (newA){
      if (oldB && !newB) { // up
        ++encValue;
      } else { // down
        --encValue;
      }
    } else {
      if (oldB && !newB) { // down
        --encValue;
      } else { // up
        ++encValue;
      }
    }
    oldB = newB;
  }
  void setup(){
    oldB=0;
    encValue=0;
    nh.advertise(pub);
    pins.setup();
    attachInterrupt(5,func,CHANGE);
    pub_msg.data=0;
  }
  void update(){
    pub_msg.data = encValue;
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

