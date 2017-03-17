#include "clsAmooNorouz.h"
#include "clsGetLandmarks.h"

using namespace cv;

clsAmooNorouz::clsAmooNorouz(stuConfig _config)
{
    this->config = _config;
    hat = imread(this->config.hatAddress, cv::IMREAD_UNCHANGED);
    beard = imread(this->config.beardAddress, cv::IMREAD_UNCHANGED);
    leftEye = imread(this->config.leftEyeAddress, cv::IMREAD_UNCHANGED);
    rightEye = imread(this->config.rightEyeAddress, cv::IMREAD_UNCHANGED);
    samsungLogo = imread(this->config.samsungLogoAddress, cv::IMREAD_UNCHANGED);
    galaxyLogo = imread(this->config.galaxyLogoAddress, cv::IMREAD_UNCHANGED);
    landmarkDetector = QSharedPointer<clsFaceLandmarkDetection>(new clsFaceLandmarkDetection(config.modelAddress));
}

cv::Mat clsAmooNorouz::getAmooNorouzImage(cv::Mat _input)
{
    cv::Mat resizedImage;
    resizedImage = this->resizeKeepAspectRatio(_input, this->config.processFrameSize);
    cv::Mat out;
    resizedImage.copyTo(out);

    std::vector<full_object_detection> fullObjects = this->landmarkDetector->getFaceLandmarks(resizedImage);
    for (unsigned long k = 0; k < fullObjects.size(); ++k)
    {
        cv::Mat eyebrows = getTransformedEyebrows(fullObjects[k], out.size());
        out = this->putOverlayOnImage(out, eyebrows);
        cv::Mat beard = getTransformedBeard(fullObjects[k], out.size());
        out = this->putOverlayOnImage(out, beard);
        cv::Mat hat = getTransformedHat(fullObjects[k], out.size());
        out = this->putOverlayOnImage(out, hat);
        cv::Mat logo = getTransformedLogo(out.size());
        out = this->putOverlayOnImage(out, logo);
    }

    return out;
}


cv::Mat clsAmooNorouz::putOverlayOnImage(cv::Mat _input, cv::Mat _overlay)
{
    cv::Mat out;
    _input.copyTo(out);
    for(int i=0 ; i<_overlay.cols; i++)
        for(int j=0 ; j<_overlay.rows; j++) {
            float opacity = (float)_overlay.at<cv::Vec4b>(j,i)[3]/255.0;
            out.at<cv::Vec3b>(j ,i) =
                    (opacity)*cv::Vec3b(_overlay.at<cv::Vec4b>(j,i)[0], _overlay.at<cv::Vec4b>(j,i)[1], _overlay.at<cv::Vec4b>(j,i)[2])
                    +(1- opacity)*out.at<cv::Vec3b>(j ,i);
        }
    return out;

}

cv::Mat clsAmooNorouz::resizeKeepAspectRatio(const cv::Mat &input, const cv::Size &dstSize)
{
    cv::Mat output;
    double h1 = dstSize.width * (input.rows/(double)input.cols);
    double w2 = dstSize.height * (input.cols/(double)input.rows);
    if( h1 <= dstSize.height) {
        cv::resize( input, output, cv::Size(dstSize.width, h1));
    } else {
        cv::resize( input, output, cv::Size(w2, dstSize.height));
    }

    return output;
}

Mat clsAmooNorouz::getTransformedBeard(full_object_detection shape, cv::Size _imageSize)
{
    std::vector<Point2f> dstPoints;
    // we use perspective for beard because it has much variation
    Mat perspectiveMatrix( 3, 3, CV_32FC1 );
    Mat outputImage;

    // beard
    for(int i=0; i<config.beardLandmarkIndexs.size(); i++)
        dstPoints.push_back(Point( shape.part(config.beardLandmarkIndexs[i]).x() , shape.part(config.beardLandmarkIndexs[i]).y() ));

    /// Get the Affine Transform
    perspectiveMatrix = findHomography( config.beardLandmarks, dstPoints ,0);
    //perspectiveMatrix = cv::estimateAffinePartial2D(config.beardLandmarks, dstPoints);
    /// Apply the Affine Transform just found to the src image
    warpPerspective(this->beard, outputImage, perspectiveMatrix, _imageSize );
    //warpAffine(this->beard, warp_dst, perspectiveMatrix, _imageSize );

    return outputImage;
}

Mat clsAmooNorouz::getTransformedEyebrows(full_object_detection shape, cv::Size _imageSize)
{
    cv::Mat outputImage;
    std::vector<Point2f> dstPoints;

    // leftEye
    for(int i=0; i<config.leftEyeLandmarkIndexs.size(); i++)
        dstPoints.push_back(Point( shape.part(config.leftEyeLandmarkIndexs[i]).x() , shape.part(config.leftEyeLandmarkIndexs[i]).y() ));

    cv::Mat affineMatrix = cv::estimateAffinePartial2D(config.leftEyeLandmarks, dstPoints);
    cv::Mat warp_dst;
    warpAffine(this->leftEye, warp_dst, affineMatrix, _imageSize );
    warp_dst.copyTo(outputImage);

    // rightEye
    dstPoints.clear();
    for(int i=0; i<config.rightEyeLandmarkIndexs.size(); i++)
        dstPoints.push_back(Point( shape.part(config.rightEyeLandmarkIndexs[i]).x() , shape.part(config.rightEyeLandmarkIndexs[i]).y() ));

    affineMatrix = cv::estimateAffinePartial2D(config.rightEyeLandmarks, dstPoints);
    warpAffine(this->rightEye, warp_dst, affineMatrix, _imageSize );
    return outputImage+warp_dst;
}

Mat clsAmooNorouz::getTransformedHat(full_object_detection shape, Size _imageSize)
{
    std::vector<Point2f> dstPoints;
    // leftEye
    for(int i=0; i<config.hatLandmarkIndexs.size(); i++)
        dstPoints.push_back(Point( shape.part(config.hatLandmarkIndexs[i]).x() , shape.part(config.hatLandmarkIndexs[i]).y() ));

    cv::Mat affineMatrix = cv::estimateAffinePartial2D(config.hatLandmarks, dstPoints);
    cv::Mat outputImage;
    warpAffine(this->hat, outputImage, affineMatrix, _imageSize );
    return outputImage;

}

Mat clsAmooNorouz::getTransformedLogo(Size _imageSize)
{
    float samsungAspectRatio =  (float)samsungLogo.rows / (float)samsungLogo.cols  ;
    float galaxyAspectRatio =  (float)galaxyLogo.rows / (float)galaxyLogo.cols  ;
    int width = this->config.samsungLogoWidthPercent * _imageSize.width;

    cv::resize(samsungLogo, samsungLogo, cv::Size(width, width * samsungAspectRatio));
    cv::resize(galaxyLogo, galaxyLogo, cv::Size(width * 0.8, width * 0.8 * galaxyAspectRatio));

    cv::Mat logo(_imageSize, CV_8UC4);
    logo.setTo(cv::Scalar::all(0));
    this->samsungLogo.copyTo(logo(cv::Rect(this->config.samsungLogoPosition.x * _imageSize.width, this->config.samsungLogoPosition.y * _imageSize.height,
                  this->samsungLogo.cols, this->samsungLogo.rows)));
    int galaxy_x = logo.cols - this->config.samsungLogoPosition.x * _imageSize.width - this->galaxyLogo.cols;
    int galaxy_y = this->config.samsungLogoPosition.y * _imageSize.height;
    this->galaxyLogo.copyTo(logo(cv::Rect(galaxy_x, galaxy_y,
                  this->galaxyLogo.cols, this->galaxyLogo.rows)));
    return logo;
}

void clsAmooNorouz::stuConfig::saveToFile(std::string _fileName)
{
    cv::FileStorage fs(_fileName, cv::FileStorage::WRITE);
    fs << "beardAddress" << beardAddress;
    fs << "leftEyeAddress" << leftEyeAddress;
    fs << "rightEyeAddress" << rightEyeAddress;
    fs << "samsungLogoAddress" << samsungLogoAddress;
    fs << "hatAddress" << hatAddress;
    fs << "modelAddress" << modelAddress;
    fs << "hatLandmarks" << hatLandmarks;
    fs << "beardLandmarks" << beardLandmarks;
    fs << "leftEyeLandmarks" << leftEyeLandmarks;
    fs << "rightEyeLandmarks" << rightEyeLandmarks;
    fs << "samsungLogoPosition" << samsungLogoPosition;
    fs << "samsungLogoHeight" << samsungLogoWidthPercent;
    fs.release();
}

bool clsAmooNorouz::stuConfig::loadFromFile(std::__cxx11::string _fileName)
{
    cv::FileStorage fs;
    if(fs.open(_fileName, cv::FileStorage::READ)) {
        fs["beardAddress"] >> beardAddress;
        fs["leftEyeAddress"] >> leftEyeAddress;
        fs["rightEyeAddress"] >> rightEyeAddress;
        fs["samsungLogoAddress"] >> samsungLogoAddress;
        fs["hatAddress"] >> hatAddress;
        fs["modelAddress"] >> modelAddress;
        fs["hatLandmarks"] >> hatLandmarks;
        fs["beardLandmarks"] >> beardLandmarks;
        fs["hatLandmarks"] >> hatLandmarks;
        fs["beardLandmarks"] >> beardLandmarks;
        fs["leftEyeLandmarks"] >> leftEyeLandmarks;
        fs["rightEyeLandmarks"] >> rightEyeLandmarks;
        fs["samsungLogoPosition"] >> samsungLogoPosition;
        fs["samsungLogoWidthPercent"] >> samsungLogoWidthPercent;
        fs.release();
        return true;
    }
    return false;
}

std::string getLandmarkAddress(std::string address) {
    QString QAddress;
    QAddress =QString::fromStdString(address);
    QString landmarkAddress = QAddress.mid(0,QAddress.lastIndexOf('.'))+"_landmarks.png";
    return landmarkAddress.toStdString();
}

bool clsAmooNorouz::stuConfig::getLandMarksFromUser()
{
    clsGetLandmarks landmark;

    cv::Mat beard = cv::imread(getLandmarkAddress(this->beardAddress));
    landmark.getLandmarkPoints(beard, beardLandmarkIndexs.size(), beardLandmarks);


    cv::Mat hat = cv::imread(getLandmarkAddress(this->hatAddress));
    landmark.getLandmarkPoints(hat, hatLandmarkIndexs.size(), hatLandmarks);

    cv::Mat leftEye = cv::imread(getLandmarkAddress(leftEyeAddress));
    landmark.getLandmarkPoints(leftEye, leftEyeLandmarkIndexs.size(), leftEyeLandmarks);
    cv::Mat rightEye = cv::imread(getLandmarkAddress(rightEyeAddress));
    landmark.getLandmarkPoints(rightEye, rightEyeLandmarkIndexs.size(), rightEyeLandmarks);
}
