#include <Arduino.h>
#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>
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
//#include <std_msgs/Empty.h>
//#include <std_msgs/Bool.h>

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
#define M3A 8
#define M3B 9

#define E0Z 2
#define E1Z 3
#define E2Z 4
#define E3Z 5

#define A0  
#define A1  
#define A2  
#define A3  

#define S0G 22
#define S0O 24
#define S0I 26

ros::NodeHandle nh;

//enc
EncZero e0,e1,e2,e3;
std_msgs::Int16 e0msg,e1msg,e2msg,e3msg;
ros::Publisher e0p("motor0/zero",&e0msg);
ros::Publisher e1p("motor1/zero",&e1msg);
ros::Publisher e2p("motor2/zero",&e2msg);
ros::Publisher e3p("motor3/zero",&e3msg);
void e0Cb(const std_msgs::Empty& msg){e0.reset();}
void e1Cb(const std_msgs::Empty& msg){e1.reset();}
void e2Cb(const std_msgs::Empty& msg){e2.reset();}
void e3Cb(const std_msgs::Empty& msg){e3.reset();}
ros::Subscriber<std_msgs::Empty>e0s("motor0/reset",&e0Cb);
ros::Subscriber<std_msgs::Empty>e1s("motor1/reset",&e1Cb);
ros::Subscriber<std_msgs::Empty>e2s("motor2/reset",&e2Cb);
ros::Subscriber<std_msgs::Empty>e3s("motor3/reset",&e3Cb);

//motor
Motor m0({M0A,M0B});
Motor m1({M1A,M1B});
Motor m2({M2A,M2B});
Motor m3({M3A,M3B});
void m0Cb(const std_msgs::Int16& msg){m0.run(msg.data);}
void m1Cb(const std_msgs::Int16& msg){m1.run(msg.data);}
void m2Cb(const std_msgs::Int16& msg){m2.run(msg.data);}
void m3Cb(const std_msgs::Int16& msg){m3.run(msg.data);}
ros::Subscriber<std_msgs::Int16>m0s("motor0/motor",&m0Cb);
ros::Subscriber<std_msgs::Int16>m1s("motor1/motor",&m1Cb);
ros::Subscriber<std_msgs::Int16>m2s("motor2/motor",&m2Cb);
ros::Subscriber<std_msgs::Int16>m3s("motor3/motor",&m3Cb);
void m0sCb(const std_msgs::Empty& msg){m0.off();}
void m1sCb(const std_msgs::Empty& msg){m1.off();}
void m2sCb(const std_msgs::Empty& msg){m2.off();}
void m3sCb(const std_msgs::Empty& msg){m3.off();}
ros::Subscriber<std_msgs::Empty>m0ss("motor0/off",&m0sCb);
ros::Subscriber<std_msgs::Empty>m1ss("motor1/off",&m1sCb);
ros::Subscriber<std_msgs::Empty>m2ss("motor2/off",&m2sCb);
ros::Subscriber<std_msgs::Empty>m3ss("motor3/off",&m3sCb);

//swhitch
O s0o(S0O);
O s0g(S0G);
I s0i(S0I);
std_msgs::Bool s0msg;
ros::Publisher s0p("switch0",&s0msg);


void setup(){
  nh.initNode();

  //encpub
  nh.advertise(e0p);
  nh.advertise(e1p);
  nh.advertise(e2p);
  nh.advertise(e3p);

  nh.subscribe(e0s);
  nh.subscribe(e1s);
  nh.subscribe(e2s);
  nh.subscribe(e3s);

  //motor
  nh.subscribe(m0s);
  nh.subscribe(m1s);
  nh.subscribe(m2s);
  nh.subscribe(m3s);

  nh.subscribe(m0ss);
  nh.subscribe(m1ss);
  nh.subscribe(m2ss);
  nh.subscribe(m3ss);

  //switch
  s0o.on();
  s0g.off();
  nh.advertise(s0p);

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

  //switchmsg
  s0msg.data=s0i.D();
  s0p.publish(&s0msg);

  nh.spinOnce();
  delay(10);
}
  
//encfunc
void E0f(){e0.pp();}
void E1f(){e1.pp();}
void E2f(){e2.pp();}
void E3f(){e3.pp();}

