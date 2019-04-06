#ifndef PIN
#define PIN

#include <Arduino.h>

class O{
  private:
    int pin_;
  public:
    O(int pin);
    void on();
    void off();
    void A(int pow);
    int pin(){return pin_;}
};

class I{
  private:
    int pin_;
  public:
    I(int pin);
    int D();
    int A();
    int pin(){return pin_;}
};

//O
O::O(int pin):pin_(pin){
  pinMode(pin_,OUTPUT);
}

void O::on(){
  digitalWrite(pin_,HIGH);
}

void O::off(){
  digitalWrite(pin_,LOW);
}

void O::A(int pow){
  analogWrite(pin_,pow);
}

//I
I::I(int pin):pin_(pin){
  pinMode(pin_,INPUT);
}

int I::D(){
  return digitalRead(pin_);
}

int I::A(){
  return analogRead(pin_);
}

#endif
