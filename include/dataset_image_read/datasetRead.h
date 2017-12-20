//datasetRead.h
#ifndef DATASETREAD_H_
#define DATASETREAD_H_

#include "ros/ros.h"
#include <std_msgs/Header.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <dataset_image_read/Dataset.h>
#include <math.h>
#include <algorithm>
#include <fstream>

namespace dataset{
class DataSet
{
public:
    DataSet();
    ~DataSet();

    void initialize();
    double kitti_dataset(cv::Mat  &im, const int imageNum);
    void tum_dataset(cv::Mat  &im, const int imageNum);
    void euroc_dataset(cv::Mat  &im, const int imageNum);
    
    std::string imagePublishName, datasetName;
    std::string datasetPathNames, imagePathNames, timeFilesPath;
    double vTimestamps;
    std::ifstream timesFiles;
    
private:
    double last_timestamps = 0;
};
    
}


#endif