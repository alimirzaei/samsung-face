#include "clsEnrichedFullObject.h"

clsEnrichedFullObject::clsEnrichedFullObject()
{

}

#define PI 3.14159265
double clsEnrichedFullObject::calculateAngle() const {
    int leftEyeX = (this->part(39).x() + this->part(36).x()) / 2;
    int leftEyeY = (this->part(39).y() + this->part(36).y()) / 2;

    int rightEyeX = (this->part(45).x() + this->part(42).x()) / 2;
    int rightEyeY = (this->part(45).y() + this->part(42).y()) / 2;

    double angle = - std::atan( float(rightEyeY - leftEyeY) / float(rightEyeX - leftEyeX) ) * 180.0 / PI;
    return angle;
}

cv::Point clsEnrichedFullObject::getHatLandmarksOnFace() const {
    int noseTopX = this->part(27).x();
    int noseTopY = this->part(27).y();

    float noseToChinHeight = this->part(8).y() - this->part(27).y();

    // TODO: This should be improved. remove magical number
    int faceLandmarkX = noseTopX;
    int faceLandmarkY = noseTopY - 0.6 * noseToChinHeight;

    return cv::Point(faceLandmarkX, faceLandmarkY);
}

cv::Point clsEnrichedFullObject::getBeardLandmarksOnFace() const {
    return cv::Point(this->part(62).x(), this->part(62).y());
}
