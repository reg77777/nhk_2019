#include <ros/ros.h>
#include <std_msgs/Float32.h>

class Sensor {
   
   public:
      Sensor();

   private:
      void Callback(const std_msgs::Float32::ConstPtr& sub_msg);
      ros::nodehandle nh;
      ros::Subscriber 

};
Sensor::Sensor() {
}
