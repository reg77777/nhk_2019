#include "motor/motor.h"

#define pinMUL_A 
#define pinMUL_B
#define pinMUR_A
#define pinMUR_B
#define pinMDR_A
#define pinMDR_B
#define pinMDL_A
#define pinMDL_B

struct MotorPins pinMUL = {pinMUL_A,pinMUL_B};
struct MotorPins pinMUR = {pinMUR_A,pinMUR_B};
struct MotorPins pinMDR = {pinMDR_A,pinMDR_B};
struct MotorPins pinMDL = {pinMDL_A,pinMDL_B};

Motor ul(pinMUL);
Motor ur(pinMUR);
Motor dr(pinMDR);
Motor dl(pinMDL);

void setup()
{
}

void loop()
{
  ul.run(100);
}
