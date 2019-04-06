#include <ros/ros.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char**argv){
  ros::init(argc,argv,"connect");
  ros::NodeHandle nh("~");

  char *command = 
    "docker run --rm --net=host --privileged --volume=/dev:/dev -it iory/docker-ros-d415:docker.d415 /bin/bash -i -c 'roslaunch realsense2_camera rs_rgbd.launch enable_pointcloud:=true align_depth:=false depth_registered_processing:=true align_depth:=true'";
  system(command);

  ROS_INFO("CONNECTING");
  return 0;
}
