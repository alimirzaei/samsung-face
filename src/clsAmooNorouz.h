#ifndef CLSAMOONOROUZ_H
#define CLSAMOONOROUZ_H
#include <QSharedPointer>
#include "clsFaceLandmarkDetection.h"

class clsAmooNorouz
{
public:
    struct stuConfig {
        stuConfig(): beardAddress("images/beard.png"), leftEyeAddress("images/eyebrow_left.png"),rightEyeAddress("images/eyebrow_right.png"),
            hatAddress("images/hat.png"), modelAddress("model/shape_predictor_68_face_landmarks.dat"),
            processFrameSize(cv::Size(640,480))
        {
        }

        std::string beardAddress, leftEyeAddress, rightEyeAddress, hatAddress, modelAddress;
        cv::Size processFrameSize;
        std::vector<int> beardLandmarkIndexs = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 33};
        std::vector<int> hatLandmarkIndexs = {0, 8, 16};
        std::vector<int> leftEyeLandmarkIndexs = {17, 18, 19, 20, 21};
        std::vector<int> rightEyeLandmarkIndexs = {22, 23, 24, 25, 26};
        std::vector<cv::Point> beardLandmarks, hatLandmarks, leftEyeLandmarks, rightEyeLandmarks;

    public:
        void saveToFile(std::string _fileName);
        bool loadFromFile(std::string _fileName);
        bool getLandMarksFromUser();
    };

    clsAmooNorouz(stuConfig config = stuConfig());
    cv::Mat getAmooNorouzImage(cv::Mat _input);

private:
    QSharedPointer<clsFaceLandmarkDetection> landmarkDetector;
    cv::Mat beard, hat, leftEye, rightEye;          // we hold images in RAM
    stuConfig config;

private:
    cv::Mat resizeKeepAspectRatio(const cv::Mat &input, const cv::Size &dstSize);
    cv::Mat getTransformedBeard(full_object_detection shape, cv::Size _imageSize);
    cv::Mat getTransformedEyebrows(full_object_detection shape, cv::Size _imageSize);
    cv::Mat getTransformedHat(full_object_detection shape, cv::Size _imageSize);
    cv::Mat putOverlayOnImage(cv::Mat _input, cv::Mat _overlay);
};

#endif // CLSAMOONOROUZ_H
