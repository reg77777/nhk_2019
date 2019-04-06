#ifndef INCLUDE_MOTOR
#define INCLUDE_MOTOR

#include <ros.h>
#include <Arduino.h>

struct MotorPins{
  int CW;
  int CCW;
};

class Motor{

  private:
    struct MotorPins pins;

  public:
    Motor(struct MotorPins pins_);
    void run(int speed);

};


#endif
