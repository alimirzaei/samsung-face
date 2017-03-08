#include "clsAmooNorouz.h"
#include "clsEnrichedFullObject.h"
clsAmooNorouz::clsAmooNorouz(stuConfig _config)
{
    this->config = _config;
    hat = imread(this->config.hatAddress, cv::IMREAD_UNCHANGED);
    beard = imread(this->config.beardAddress, cv::IMREAD_UNCHANGED);
    eyebrow = imread(this->config.eyebrowAddress, cv::IMREAD_UNCHANGED);
}

cv::Mat clsAmooNorouz::getAmooNorouzImage(cv::Mat _input)
{
    try
    {
        cv::Mat out;
        _input.copyTo(out);
        std::vector<full_object_detection> fullObjects = this->landmarkDetector.getFaceLandmarks(_input);
        for (unsigned long k = 0; k < fullObjects.size(); ++k)
        {
            cv::Mat resized_hat, resized_beard;

            cv::Point resizedHatLandmark;
            //cv::Point hatLandmark(950, 1500); // TODO: These numbers should be read from config file
            resizeWearable(hat, resized_hat, fullObjects[k], config.hatLandmark, resizedHatLandmark, 2);

            cv::Point resizedBeardLandmark;
            //cv::Point beardLandmark(1200, 1800); // TODO: These numbers should be read from config file
            resizeWearable(beard, resized_beard, fullObjects[k], config.beardLandmark, resizedBeardLandmark, 2.8);

            // calculation of face angle
            double angle = ((clsEnrichedFullObject*)(&fullObjects[k]))->calculateAngle();

            // rotate resized hat and beard based on calculated angle
            cv::Mat rotated_hat, rotated_beard;
            cv::Point rotatedHatLandmark;
            rotateWearable(resized_hat, rotated_hat, angle, resizedHatLandmark, rotatedHatLandmark);
            cv::Point rotatedBeardLandmark;
            rotateWearable(resized_beard, rotated_beard, angle, resizedBeardLandmark, rotatedBeardLandmark);

            cv::Point shiftHatLandmark(rotatedHatLandmark.x - ((clsEnrichedFullObject*)(&fullObjects[k]))->getHatLandmarksOnFace().x,
                                       rotatedHatLandmark.y - ((clsEnrichedFullObject*)(&fullObjects[k]))->getHatLandmarksOnFace().y);

            cv::Point shiftBeardLandmark(rotatedBeardLandmark.x - ((clsEnrichedFullObject*)(&fullObjects[k]))->getBeardLandmarksOnFace().x,
                                       rotatedBeardLandmark.y - ((clsEnrichedFullObject*)(&fullObjects[k]))->getBeardLandmarksOnFace().y);


            for(int i=0 ; i<rotated_hat.cols; i++)
                for(int j=0 ; j<rotated_hat.rows; j++) {
                    if(rotated_hat.at<cv::Vec4b>(j,i)[3] != 0)
                        out.at<cv::Vec3b>(j - shiftHatLandmark.y ,i - shiftHatLandmark.x) =
                           cv::Vec3b(rotated_hat.at<cv::Vec4b>(j,i)[0], rotated_hat.at<cv::Vec4b>(j,i)[1], rotated_hat.at<cv::Vec4b>(j,i)[2]);

                }

            for(int i=0 ; i<rotated_beard.cols; i++)
                for(int j=0 ; j<rotated_beard.rows; j++) {
                    if(rotated_beard.at<cv::Vec4b>(j,i)[3] != 0)
                        out.at<cv::Vec3b>(j - shiftBeardLandmark.y ,i - shiftBeardLandmark.x) =
                           cv::Vec3b(rotated_beard.at<cv::Vec4b>(j,i)[0], rotated_beard.at<cv::Vec4b>(j,i)[1], rotated_beard.at<cv::Vec4b>(j,i)[2]);

                }


        }

        return out;
    }
    catch (std::exception& e)
    {
        std::cout << "\nexception thrown!" << std::endl;
        std::cout << e.what() << std::endl;
    }
}

void clsAmooNorouz::resizeWearable(cv::InputArray src, cv::OutputArray dst, full_object_detection shape, cv::Point2i wearableLandmark, cv::Point2i &resizedWearableLandmark, float widthRatio) {
    float faceWidth = sqrt( pow(shape.part(16).y() - shape.part(0).y(), 2) + pow(shape.part(16).x() - shape.part(0).x(), 2) );
    float resizedWidth = faceWidth * widthRatio;
    float resizedHeight = src.rows() * faceWidth * widthRatio / src.cols();

    resizedWearableLandmark.x = (resizedWidth / src.cols()) * wearableLandmark.x;
    resizedWearableLandmark.y = (resizedHeight / src.rows()) * wearableLandmark.y;

    cv::resize(src, dst, cv::Size(resizedWidth, resizedHeight));
}

void clsAmooNorouz::rotateWearable(cv::InputArray src, cv::OutputArray dst, double angle, cv::Point resizedLandmark, cv::Point &rotatedLandmark) {
    // get rotation matrix for rotating the image around its center
    cv::Point2f center(src.cols()/2.0, src.rows()/2.0);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    // determine bounding rectangle
    cv::Rect bbox = cv::RotatedRect(center,src.size(), angle).boundingRect();
    // adjust transformation matrix
    rot.at<double>(0,2) += bbox.width/2.0 - center.x;
    rot.at<double>(1,2) += bbox.height/2.0 - center.y;
    std::vector<cv::Point> points, points_out;
    points.push_back(resizedLandmark);
    cv::transform(points, points_out, rot);
    rotatedLandmark = points_out[0];
    cv::warpAffine(src, dst, rot, bbox.size());
}

void clsAmooNorouz::stuConfig::saveToFile(std::string _fileName)
{
    cv::FileStorage fs("config.xml", cv::FileStorage::WRITE);
    fs << "beardAddress" << beardAddress;
    fs << "eyebrowAddress" << eyebrowAddress;
    fs << "hatAddress" << hatAddress;
    fs << "modelAddress" << modelAddress;
    fs << "hatLandmark" << hatLandmark;
    fs << "beardLandmark" << beardLandmark;
    fs.release();
}

bool clsAmooNorouz::stuConfig::loadFromFile(std::__cxx11::string _fileName)
{
    cv::FileStorage fs;
    if(fs.open(_fileName, cv::FileStorage::READ)) {
        fs["beardAddress"] >> beardAddress;
        fs["eyebrowAddress"] >> eyebrowAddress;
        fs["hatAddress"] >> hatAddress;
        fs["modelAddress"] >> modelAddress;
        fs["hatLandmark"] >> hatLandmark;
        fs["beardLandmark"] >> beardLandmark;
        fs.release();
        return true;
    }

    return false;

}
