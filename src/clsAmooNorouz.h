#ifndef CLSAMOONOROUZ_H
#define CLSAMOONOROUZ_H
#include <QSharedPointer>
#include "clsFaceLandmarkDetection.h"

class clsAmooNorouz
{
public:
    struct stuConfig {
        stuConfig(): beardAddress("images/beard.png"), eyebrowAddress("images/eyebrow.png"),
            hatAddress("images/hat.png"), modelAddress("model/shape_predictor_68_face_landmarks.dat"),
            hatLandmark(cv::Point(950, 1500)), beardLandmark(cv::Point(1200, 1800))
        { }

        void saveToFile(std::string _fileName);
        bool loadFromFile(std::string _fileName);
        std::string beardAddress, eyebrowAddress, hatAddress, modelAddress;
        cv::Point hatLandmark, beardLandmark;

    };

    clsAmooNorouz(stuConfig config = stuConfig());
    cv::Mat getAmooNorouzImage(cv::Mat _input);

private:
    QSharedPointer<clsFaceLandmarkDetection> landmarkDetector;
    cv::Mat beard, hat, eyebrow;
    stuConfig config;
private:
    // TODO: change wearable to sth else!
    void resizeWearable (cv::InputArray src, cv::OutputArray dst, full_object_detection shape, cv::Point2i wearableLandmark, cv::Point2i& resizedWearableLandmark, float widthRatio);
    void rotateWearable(cv::InputArray src, cv::OutputArray dst, double angle, cv::Point resizedLandmark, cv::Point& rotatedLandmark);
};

#endif // CLSAMOONOROUZ_H
