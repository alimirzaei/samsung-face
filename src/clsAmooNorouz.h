#ifndef CLSAMOONOROUZ_H
#define CLSAMOONOROUZ_H

#include "clsFaceLandmarkDetection.h"

class clsAmooNorouz
{
public:
    struct stuConfig {
        stuConfig(): beardAddress("images/beared.png"), eyebrowAddress("images/eyebrow.png"),
            hatAddress("images/hat.png"), modelAddress("model/shape_predictor_68_face_landmarks.dat"),
            hatLandmark(cv::Point(950, 1500)), beardLandmark(cv::Point(1200, 1800))
        { }
        std::string beardAddress, eyebrowAddress, hatAddress, modelAddress;
        cv::Point hatLandmark, beardLandmark;

    };

    clsAmooNorouz(stuConfig config = stuConfig());
    cv::Mat getAmooNorouzImage(cv::Mat _input);

private:
    clsFaceLandmarkDetection landmarkDetector;
    cv::Mat beard, hat, eyebrow;
    stuConfig config;
private:
    // TODO: change wearable to sth else!
    void resizeWearable (cv::InputArray src, cv::OutputArray dst, full_object_detection shape, cv::Point2i wearableLandmark, cv::Point2i& resizedWearableLandmark, float widthRatio);
    void rotateWearable(cv::InputArray src, cv::OutputArray dst, double angle, cv::Point resizedLandmark, cv::Point& rotatedLandmark);
};

#endif // CLSAMOONOROUZ_H