#ifndef CLSGETLANDMARKS_H
#define CLSGETLANDMARKS_H

#include <opencv2/opencv.hpp>
struct stuInfo {
    cv::Mat image;
    std::vector<cv::Point> points;
    std::string title;
};

void mouseHandler(int event, int x, int y, int flags, void* param);

class clsGetLandmarks
{
public:
    clsGetLandmarks();
    void getLandmarkPoints(const cv::Mat _input, int _numberOfPoints, std::vector<cv::Point> &_points);
};

#endif // CLSGETLANDMARKS_H
