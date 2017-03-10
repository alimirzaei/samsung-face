#include "clsGetLandmarks.h"

void mouseHandler(int event, int x, int y, int flags, void* param){

    stuInfo * info = (stuInfo *) param;
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        /* left button clicked. ROI selection begins */
        info->points.push_back(cv::Point(x, y));
        cv::circle(info->image, cv::Point(x, y), 3, 255, 3);
    }
    cv::imshow(info->title, info->image);
    cv::waitKey(0);
}

clsGetLandmarks::clsGetLandmarks()
{

}

void clsGetLandmarks::getLandmarkPoints(const cv::Mat _input, int _numberOfPoints, std::vector<cv::Point> &_points)
{


    cv::Mat image;
    _input.copyTo(image);
    std::string title = "Click to enter " + std::to_string(_numberOfPoints) +" points and finally press enter";
    stuInfo myInfo;
    myInfo.image = image.clone();
    myInfo.title = title;
    cv::imshow(title, image);
    cv::setMouseCallback(title, mouseHandler, (void*)&myInfo);
    cv::waitKey(0);
    cv::destroyWindow(title);
    _points = myInfo.points;


}
