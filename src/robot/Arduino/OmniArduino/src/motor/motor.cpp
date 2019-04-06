#include "motor.h"

Motor::Motor(struct MotorPins pins_)
  :pins(pins_){
    pinMode(pins.CW,OUTPUT);
    pinMode(pins.CCW,OUTPUT);
}

void Motor::run(int speed){
  if(speed>255)speed=255;
  else if(speed<-255)speed=-255;

  if(speed>0){
    analogWrite(pins.CW,speed);
    analogWrite(pins.CCW,0);
  }
  else{
    analogWrite(pins.CW,0);
    analogWrite(pins.CCW,-speed);
  }
}
