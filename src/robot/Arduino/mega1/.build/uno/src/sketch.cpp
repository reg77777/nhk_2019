#include <Arduino.h>
#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include "module/pin.h"
#include "module/motor.h"
#include "module/air.h"
#include "module/enc.h"
void setup();
void loop();
void E0f();
void E1f();
void E2f();
void E3f();
#line 1 "src/sketch.ino"
//#include <Arduino.h>
//#include <ros.h>
//#include <std_msgs/Int16.h>

//#include "module/pin.h"
//#include "module/motor.h"
//#include "module/air.h"
//#include "module/enc.h"

#define M0A 2
#define M0B 3
#define M1A 4
#define M1B 5
#define M2A 6
#define M2B 7
#define M3A 45
#define M3B 46

#define E0Z 2
#define E1Z 3
#define E2Z 4
#define E3Z 5

#define A0  
#define A1  
#define A2  
#define A3  

ros::NodeHandle nh;

//enc
EncZero e0,e1,e2,e3;
std_msgs::Int16 e0msg,e1msg,e2msg,e3msg;
ros::Publisher e0p("motor0/enc",&e0msg);
ros::Publisher e1p("motor1/enc",&e1msg);
ros::Publisher e2p("motor2/enc",&e2msg);
ros::Publisher e3p("motor3/enc",&e3msg);

//motor
Motor m0({M0A,M0B});
Motor m1({M1A,M1B});
Motor m2({M2A,M2B});
Motor m3({M3A,M3B});
void m0sCb(const std_msgs::Int16& msg){}
void m1sCb(const std_msgs::Int16& msg){}
void m2sCb(const std_msgs::Int16& msg){}
void m3sCb(const std_msgs::Int16& msg){}
ros::Subscriber<std_msgs::Int16>m0s("motor0/motor",&m0sCb);
ros::Subscriber<std_msgs::Int16>m1s("motor1/motor",&m1sCb);
ros::Subscriber<std_msgs::Int16>m2s("motor2/motor",&m2sCb);
ros::Subscriber<std_msgs::Int16>m3s("motor3/motor",&m3sCb);

void setup(){
  nh.initNode();

  //encpub
  nh.advertise(e0p);
  nh.advertise(e1p);
  nh.advertise(e2p);
  nh.advertise(e3p);

  //motor
  nh.subscribe(m0s);
  nh.subscribe(m1s);
  nh.subscribe(m2s);
  nh.subscribe(m3s);

  //encInterrupt
  attachInterrupt(E0Z,E0f,FALLING);
  attachInterrupt(E1Z,E1f,FALLING);
  attachInterrupt(E2Z,E2f,FALLING);
  attachInterrupt(E3Z,E3f,FALLING);
}

void loop(){

  //encmsg
  e0msg.data=e0.c();
  e1msg.data=e1.c();
  e2msg.data=e2.c();
  e3msg.data=e3.c();

  //encpub
  e0p.publish(&e0msg);
  e1p.publish(&e1msg);
  e2p.publish(&e2msg);
  e3p.publish(&e3msg);

  nh.spinOnce();
  delay(10);
}
  
//encfunc
void E0f(){e0.pp();}
void E1f(){e1.pp();}
void E2f(){e2.pp();}
void E3f(){e3.pp();}

