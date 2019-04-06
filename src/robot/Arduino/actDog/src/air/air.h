#ifndef INCLUDE_AIR
#define INCLUDE_AIR

class Air {

   int pin_;
   string topic_name_;
   
   public:
      Air(int pin,ros::NodeHandle nh,const char* s);
      void on();
      void off();

};

#endif
