#ifndef ENRICHEDFULLOBJECT_H
#define ENRICHEDFULLOBJECT_H

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <opencv2/opencv.hpp>

using namespace dlib;
class clsEnrichedFullObject : public full_object_detection
{
public:
    clsEnrichedFullObject();
double calculateAngle() const;
cv::Point getHatLandmarksOnFace () const;
cv::Point getBeardLandmarksOnFace () const;
};

#endif // ENRICHEDFULLOBJECT_H
