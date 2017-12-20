#include "datasetRead.h"
namespace dataset{
DataSet::DataSet()
{
    ROS_INFO("Starting datasetRead......");
}

DataSet::~DataSet()
{
    ROS_INFO("Destroying datasetRead......");
}
void DataSet::initialize()
{
    ros::param::get("~image_publishName", imagePublishName);
    ros::param::get("~dataset_name", datasetName);
    ros::param::get("~datasetPath_names", datasetPathNames);
    if(datasetName == "kitti")
    {
	timeFilesPath = datasetPathNames+ "times.txt";
	//std::cout << timeFilesPath << std::endl;
	timesFiles.open(timeFilesPath.c_str());
    }
        
//     ros::param::get("~image_publishName", imagePublishName);
//     ros::param::get("~dataset_name", datasetName);

}
double DataSet::kitti_dataset(cv::Mat  &im, const int imageNum)
{
    std::stringstream imageNumPart;
    std::string timeStr;
    double timeV = 0;
    imageNumPart << std::setfill('0') << std::setw(6) << imageNum;
    imagePathNames = datasetPathNames + "image_0/" + imageNumPart.str() + ".png";
    im = cv::imread(imagePathNames, CV_LOAD_IMAGE_UNCHANGED);
    //std::cout << imagePathNames << std::endl;  //output image path and name

    getline(timesFiles,timeStr);
    if(!timeStr.empty())
    {
	std::stringstream ss;   //string type conversion with other type
	ss << timeStr;
        ss >> timeV;
	if(last_timestamps > timeV)
	    ROS_ERROR("have a time stamp abnormal");
	last_timestamps = timeV;
	
    }
    return timeV;
}

void DataSet::tum_dataset(cv::Mat  &im, const int imageNum)
{
    
}

void DataSet::euroc_dataset(cv::Mat  &im, const int imageNum)
{
    
}
}
