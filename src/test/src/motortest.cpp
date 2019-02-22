#include <ros/ros.h>
#include <std_msgs/Float32.h>

class Motortester{
   public:
      Motortester();
   private:
      ros::NodeHandle nh;
      float speed;
      int which;
}

Motortester::Motertester(){
   which = 0;
   speed = 100;
}

int main(int argc, char const* argv[])
{
   ros::init(argc,argv,"motortester");
   Motortester motertester();
   ros::Rate loop_rate(10);
   while(ros::ok()){
      motortester.publish();
      ros::spinOnce();
      loop_rate.sleep();
   }
   return 0;
}
