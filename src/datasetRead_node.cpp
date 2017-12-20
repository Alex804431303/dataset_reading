#include "datasetRead.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "datasetRead_node");
    ros::NodeHandle nh_;
    ros::Publisher dataset_rect_pub;
    dataset::DataSet datasetNode;
    int imgNum = 0;
    double timeValue = 0;
    cv::Mat src_img;
    dataset_image_read::Dataset DatesetMsg;
    sensor_msgs::ImagePtr imgMsg;
    datasetNode.initialize();
    ros::Rate loop_rate(30);
    dataset_rect_pub = nh_.advertise<dataset_image_read::Dataset>(datasetNode.imagePublishName, 1);
    while(ros::ok())
    {   
	if(datasetNode.datasetName == "kitti")  timeValue = datasetNode.kitti_dataset(src_img, imgNum);
	else if(datasetNode.datasetName == "tum") datasetNode.tum_dataset(src_img, imgNum);
	else if(datasetNode.datasetName == "euroc") datasetNode.euroc_dataset(src_img, imgNum);
	else 
	{
	    ROS_ERROR("error dataset name input");
	    ros::shutdown();
	    return -1;
	}
	if(src_img.empty())
	{
	    ROS_ERROR("no image imput");
	    ros::shutdown();
	    return -1;
	}
	if(src_img.channels() == 3) imgMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", src_img).toImageMsg();
	else imgMsg = cv_bridge::CvImage(std_msgs::Header(), "mono8", src_img).toImageMsg();
	DatesetMsg.timeStamp = timeValue;
	DatesetMsg.datasetImage = imgMsg.operator*();  //ImagePtr change to image's msg
	dataset_rect_pub.publish(DatesetMsg);
        ros::spinOnce();
        loop_rate.sleep();
	cv::namedWindow("kitti");
	cv::imshow("kitti", src_img);
	cv::waitKey(1);
    }
    ros::spin();
    return 0;
}


