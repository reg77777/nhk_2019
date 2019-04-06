#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc,char**argv){
  ros::NodeHandle nh;
  ros::init(argc,argv,"broadcast");

  tf::TransformBroadcast br;
  return 0;
}
