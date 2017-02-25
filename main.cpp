#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// Function Headers
void detectAndDisplay(Mat frame);

// Global variables
// Copy this file from opencv/data/haarscascades to target folder
string face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
int filenumber; // Number of file to be saved
string filename;

// Function main
int main(void)
{
    // Load the cascade
    if (!face_cascade.load(face_cascade_name)){
        printf("--(!)Error loading\n");
        return (-1);
    }

    // Read the image file
    Mat frame = imread("/home/ali/Downloads/COP7-SideEvent_-_1.JPG");
    cv::resize(frame, frame, frame.size()/5);
    Mat hat = imread("/home/ali/Projects/face/hat.png", IMREAD_UNCHANGED);
    Mat beard = imread("/home/ali/Projects/face/beard.png", IMREAD_UNCHANGED);
    //cv::copyMakeBorder(frame, frame, 100, 100,0,0,cv::BORDER_CONSTANT);
    //std::cout << hat.channels() << beard.channels();
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    //cv::cvtColor(frame, frame, CV_BGR2RGBA);
    cv::Mat out;
    frame.copyTo(out);
    for(cv::Rect& face : faces) {
        cv::Mat resized_hat, resized_beard;
        cv::resize(hat, resized_hat,cv::Size(face.width*1.3, hat.rows*face.width*1.3/hat.cols));
        cv::resize(beard, resized_beard,cv::Size(face.width*0.9, beard.rows*face.width*0.9/beard.cols));
        for(int i=0 ; i<resized_hat.cols; i++)
            for(int j=0 ; j<resized_hat.rows; j++) {
                if(resized_hat.at<Vec4b>(j,i)[3] != 0)
                    out.at<Vec3b>(j+1.1*face.y-resized_hat.rows,i+face.x-0.15*face.width) = Vec3b(resized_hat.at<Vec4b>(j,i)[0], resized_hat.at<Vec4b>(j,i)[1], resized_hat.at<Vec4b>(j,i)[2]);

            }
        for(int i=0 ; i<resized_beard.cols; i++)
            for(int j=0 ; j<resized_beard.rows; j++) {

                if(resized_beard.at<Vec4b>(j,i)[3] != 0)
                    out.at<Vec3b>(j+face.y+face.height*.5,i+face.x+0.05*face.width) = Vec3b(resized_beard.at<Vec4b>(j,i)[0], resized_beard.at<Vec4b>(j,i)[1], resized_beard.at<Vec4b>(j,i)[2]);

            }

        //resized_hat.copyTo(frame(cv::Rect(face.x, face.y-resized_hat.rows, resized_hat.cols, resized_hat.rows))) ;
        //resized_beard.copyTo(frame(cv::Rect(face.x, face.y+face.height, resized_beard.cols, resized_beard.rows))) ;
    }
    cv::imshow("", out);
    cv::waitKey(0);

    return 0;
}

//// Function detectAndDisplay
//void detectAndDisplay(Mat frame)
//{
//    std::vector<Rect> faces;
//    Mat frame_gray;
//    Mat crop;
//    Mat res;
//    Mat gray;
//    string text;
//    stringstream sstm;

//    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
//    equalizeHist(frame_gray, frame_gray);

//    // Detect faces
//    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(5, 5));

//    // Set Region of Interest
//    cv::Rect roi_b;
//    cv::Rect roi_c;

//    size_t ic = 0; // ic is index of current element
//    int ac = 0; // ac is area of current element

//    size_t ib = 0; // ib is index of biggest element
//    int ab = 0; // ab is area of biggest element

//    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

//    {
//        roi_c.x = faces[ic].x;
//        roi_c.y = faces[ic].y;
//        roi_c.width = (faces[ic].width);
//        roi_c.height = (faces[ic].height);

//        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

//        roi_b.x = faces[ib].x;
//        roi_b.y = faces[ib].y;
//        roi_b.width = (faces[ib].width);
//        roi_b.height = (faces[ib].height);

//        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

//        if (ac > ab)
//        {
//            ib = ic;
//            roi_b.x = faces[ib].x;
//            roi_b.y = faces[ib].y;
//            roi_b.width = (faces[ib].width);
//            roi_b.height = (faces[ib].height);
//        }

//        crop = frame(roi_b);
//        resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
//        cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

//        // Form a filename
//        filename = "";
//        stringstream ssfn;
//        ssfn << filenumber << ".png";
//        filename = ssfn.str();
//        filenumber++;

//        imwrite(filename, gray);

//        Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
//        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
//        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
//    }

//    // Show image
//    sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
//    text = sstm.str();

//    putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
//    imshow("original", frame);

//    if (!crop.empty())
//    {
//        imshow("detected", crop);
//    }
//    else
//        destroyWindow("detected");
//}
