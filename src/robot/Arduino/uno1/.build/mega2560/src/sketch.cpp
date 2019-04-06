#include <Arduino.h>

void s0f();
void setup();
void loop();
#line 1 "src/sketch.ino"
#define S0 0

void s0f(){
  Serial.println("a");
}

void setup()
{
  pinMode(INPUT,2);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(digitalRead(2));
}
