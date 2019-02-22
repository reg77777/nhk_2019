#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

#ifndef PI
#define PI 3.1415926535
#endif

int main(int argc, char** argv){
   ros::init(argc,argv,"usbcam");
   ros::NodeHandle nh("~");

   image_transport::ImageTransport it(nh);
   image_transport::Publisher image_pub = it.advertise("image",10);

   cv::Mat image;
   cv::Mat HSV;
   cv::VideoCapture camera(0);

   if(!camera.isOpened()){
      ROS_INFO("failed to open camera.");
      return -1;
   }

   ros::Rate looprate(10);

   std::vector<cv::Vec2d> lines;
   int w_low = 50;
   int w_up = 255;
   cv::Scalar low = cv::Scalar(0,0,130);
   cv::Scalar high = cv::Scalar(180,50,250);
   while(ros::ok()){
      camera >> image;
      //cv::Canny(image,out,image.rows*0.1,image.rows*0.1,3,false);

      cvtColor(image,HSV,CV_BGR2HSV,3);

      cv::inRange(HSV,low,high,HSV);
      /*
      cv::HoughLines(out,lines,1,PI/180.0,100,0,0);

      std::vector<cv::Vec2d>::iterator it=lines.begin();
      for(;it!=lines.end();++it){
         double rho=(*it)[0],theta=(*it)[1];
         cv::Point pt1,pt2;
         double a=cos(theta),b=sin(theta);
         double x0=a*rho,y0=b*rho;
         pt1.x = cv::saturate_cast<int>(x0+1000*(-b));
         pt1.y = cv::saturate_cast<int>(y0+1000*a);
         pt2.x = cv::saturate_cast<int>(x0-1000*(-b));
         pt2.y = cv::saturate_cast<int>(y0-1000*a);
         cv::line(image,pt1,pt2,cv::Scalar(0,0,255),1,CV_AA);
      }
      */

      cv::namedWindow("usbcam",cv::WINDOW_AUTOSIZE);
      cv::resizeWindow("usbcam",1000,1000);
      cv::imshow("usbcam",HSV);
      cv::waitKey(10);

      sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgr8",image).toImageMsg();
      image_pub.publish(msg);
      ros::spinOnce();
      looprate.sleep();
   }
   cv::destroyAllWindows();
   return 0;
}
