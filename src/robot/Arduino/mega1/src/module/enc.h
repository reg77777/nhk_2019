#ifndef ENC
#define ENC

#include "Arduino.h"
#include "pin.h"

class EncZero{
  private:
    int c_;
  public:
    EncZero():c_(0){}
    void reset(){c_=0;}
    void pp(){c_++;}
    void mm(){c_--;}
    int c(){return c_;}
};


#endif
