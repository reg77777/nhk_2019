#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h> #include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/Int32.h>

static const std::string OPENCV_WINDOW = "Image window";
static const std::string OPENCV_WINDOW2 = "Image window grey";

class ImageConverter {
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  std::vector<cv::Vec2d> lines;
  cv::Scalar low = cv::Scalar(0,0,130);
  cv::Scalar high = cv::Scalar(180,30,250);
  cv::Mat HSV;
  ros::Publisher x_pub;
  ros::Publisher y_pub;
  std_msgs::Int32 x;
  std_msgs::Int32 y;

  public:
    ImageConverter():it_(nh_){
      image_sub_ = it_.subscribe("/camera/color/image_raw",1,
          //"/camera/aligned_depth_to_color/image_raw",1,
         &ImageConverter::imageCb,this);
      image_pub_ = it_.advertise("/image_converter/output_video",1);
      cv::namedWindow(OPENCV_WINDOW);
      cv::namedWindow(OPENCV_WINDOW2);
      x_pub = nh_.advertise<std_msgs::Int32>("center_x",1);
      y_pub = nh_.advertise<std_msgs::Int32>("center_y",1);
    }

    ~ImageConverter(){
      cv::destroyWindow(OPENCV_WINDOW);
      cv::destroyWindow(OPENCV_WINDOW2);
    }

    void imageCb(const sensor_msgs::ImageConstPtr& msg){
      cv_bridge::CvImagePtr cv_ptr;
      try{
        cv_ptr = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
      }
      catch (cv_bridge::Exception& e){
        ROS_ERROR("cv_bridge exception: %s",e.what());
        return ;
      }

      cvtColor(cv_ptr->image,HSV,CV_BGR2HSV,3);
      cv::inRange(HSV,low,high,HSV);

      cv::Moments mu = moments(HSV,false);

      x.data=mu.m10/mu.m00;
      y.data=mu.m01/mu.m00;
      x_pub.publish(x);
      y_pub.publish(y);

      cv::Point2f mc = cv::Point2f(x.data,y.data);
      cv::circle(cv_ptr->image,mc,20,cv::Scalar(255,0,0),10,4);
      cv::imshow(OPENCV_WINDOW,cv_ptr->image);
      cv::imshow(OPENCV_WINDOW2,HSV);
      cv::waitKey(3);

    }
};

int main(int argc,char**argv){
  ros::init(argc,argv,"deep");
  ImageConverter ic;
  ros::spin();
  return 0;
}
