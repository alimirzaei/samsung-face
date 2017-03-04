#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>
#include <iostream>
//#include <QElapsedTimer>
//#include <QDebug>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <math.h>  /* atan */

using namespace std;
using namespace dlib;

#if defined(WIN32) || defined(_WIN32)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#ifndef FACE_LANDMARK_DETECTION_EX_H
#define FACE_LANDMARK_DETECTION_EX_H

extern "C" {

void resizeWearable (cv::InputArray src, cv::OutputArray dst, full_object_detection shape, cv::Point2i wearableLandmark, cv::Point2i& resizedWearableLandmark, float widthRatio);
void rotateWearable(cv::InputArray src, cv::OutputArray dst, double angle, cv::Point resizedLandmark, cv::Point& rotatedLandmark);
double calculateAngle(full_object_detection shape);
cv::Point getHatLandmarksOnFace (full_object_detection shape);
cv::Point getBeardLandmarksOnFace (full_object_detection shape);
EXPORT void amooNowroozMaker(char* inputAddress, char* outputAddress);

}

#endif // FACE_LANDMARK_DETECTION_EX_H
