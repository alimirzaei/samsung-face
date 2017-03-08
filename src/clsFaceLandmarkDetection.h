#ifndef CLSFACELANDMARKDETECTION_H
#define CLSFACELANDMARKDETECTION_H

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>

using namespace dlib;
class clsFaceLandmarkDetection
{
public:
    clsFaceLandmarkDetection(std::string _modelAddress = "model/shape_predictor_68_face_landmarks.dat");
    std::vector<full_object_detection> getFaceLandmarks(const cv::Mat &img);

private:
    frontal_face_detector detector;
    shape_predictor shapePredictor;
};

#endif // CLSFACELANDMARKDETECTION_H
