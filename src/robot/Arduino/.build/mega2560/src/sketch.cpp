#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include "nh/nh.h"
#include "nh/publisher.h"
#include "nh/subscriber.h"
#include <std_msgs/Int16.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
#define USE_USBCON

//#include <ros.h>
//#include <std_msgs/Float32.h>
//#include "nh/nh.h"
//#include "nh/publisher.h"
//#include "nh/subscriber.h"
//#include <std_msgs/Int16.h>

void setup(){
  setSubscriber();
  publisherSetup();
  nh.initNode();
}

void loop(){
  publish();
  nh.spinOnce();

  delay(5);
}
