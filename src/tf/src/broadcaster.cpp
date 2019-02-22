#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

class Bloadcaster{
   public:
      Bloadcaster();
   private:
      ros::NodeHandle nh;

      ros::Subscriber enc1_pose;
      ros::Subscriber enc2_pose;
      ros::Subscriber enc3_pose;
      ros::Subscriber enc4_pose;

      static tf::TransformBroadcaster br;
}
