#ifndef AIR
#define AIr

#include <Arduino.h>
#include "pin.h"

class Air{
  private:
    O o_;
  public:
    Air(O o):o_(o){}
    void on();
    void off();
};

//Air
void Air::on(){
  o_.on();
}

void Air::off(){
  o_.off();
}

#endif 
