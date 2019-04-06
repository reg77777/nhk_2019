#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc,char **argv){
  ros::init(argc,argv,"time");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<std_msgs::Int32>("time",10);

  std_msgs::Int32 msg;
  msg.data=0;

  ros::Rate loop_rate(1);
  while(ros::ok()){
    msg.data+=10000;
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
