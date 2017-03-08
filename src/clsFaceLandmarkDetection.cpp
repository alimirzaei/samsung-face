#include "clsFaceLandmarkDetection.h"

clsFaceLandmarkDetection::clsFaceLandmarkDetection(std::string _modelAddress)
{
    this->detector = get_frontal_face_detector();
    deserialize(_modelAddress) >> this->shapePredictor;

}

std::vector<full_object_detection> clsFaceLandmarkDetection::getFaceLandmarks(const cv::Mat &_img)
{
    std::vector<rectangle> dets = this->detector(dlib::cv_image<bgr_pixel>(_img));
    // Now we will go ask the shape_predictor to tell us the pose of each face we detected.
    std::vector<full_object_detection> shapes;
    for (unsigned long j = 0; j < dets.size(); ++j)
    {
        full_object_detection shape = this->shapePredictor(cv_image<bgr_pixel>(_img), dets[j]);
        shapes.push_back(shape);
    }
    return shapes;
}
