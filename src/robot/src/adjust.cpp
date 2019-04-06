#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <robot/sample1Config.h>

void callback(robot::sample1Config &config,uint32_t level){
  ROS_INFO("Reconfigure: %d %f %s %s %d",
      config.int_param,config.double_param,
      config.str_param.c_str(),
      config.bool_param?"True":"False",
      config.size);
}

int main(int argc,char**argv){
  ros::init(argc,argv,"adjust");

  dynamic_reconfigure::Server<robot::sample1Config>server;
  dynamic_reconfigure::Server<robot::sample1Config>::CallbackType f;

  f = boost::bind(&callback,_1,_2);
  server.setCallback(f);

  ROS_INFO("Spinning node");
  ros::spin();
  return 0;
}
