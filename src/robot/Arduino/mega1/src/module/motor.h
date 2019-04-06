#ifndef MOTOR
#define MOTOR

#include <Arduino.h>
#include "pin.h"

class Motor{
  private:
    O CW_,CCW_;
  public:
    Motor(O CW,O CCW):CW_(CW),CCW_(CCW){}
    void run(int pow);
    void off();
};

//Motor
void Motor::run(int pow){
  if(pow>0){
    CW_.A(pow);
    CCW_.off();
  }
  else{
    CCW_.A(-pow);
    CCW_.off();
  }
}

void Motor::off(){
  CW_.off();
  CCW_.off();
}

#endif
