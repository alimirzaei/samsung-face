#include "face_landmark_detection_ex.h"

using namespace std;
using namespace dlib;

extern "C" {

// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.



    This face detector is made using the classic Histogram of Oriented
    Gradients (HOG) feature combined with a linear classifier, an image pyramid,
    and sliding window detection scheme.  The pose estimator was created by
    using dlib's implementation of the paper:
        One Millisecond Face Alignment with an Ensemble of Regression Trees by
        Vahid Kazemi and Josephine Sullivan, CVPR 2014
    and was trained on the iBUG 300-W face landmark dataset.

    Also, note that you can train your own models using dlib's machine learning
    tools.  See train_shape_predictor_ex.cpp to see an example.




    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.
*/

// TODO: change wearable to sth else!
void resizeWearable (cv::InputArray src, cv::OutputArray dst, full_object_detection shape, cv::Point2i wearableLandmark, cv::Point2i& resizedWearableLandmark, float widthRatio) {
    float faceWidth = sqrt( pow(shape.part(16).y() - shape.part(0).y(), 2) + pow(shape.part(16).x() - shape.part(0).x(), 2) );
    float resizedWidth = faceWidth * widthRatio;
    float resizedHeight = src.rows() * faceWidth * widthRatio / src.cols();

    resizedWearableLandmark.x = (resizedWidth / src.cols()) * wearableLandmark.x;
    resizedWearableLandmark.y = (resizedHeight / src.rows()) * wearableLandmark.y;

    cv::resize(src, dst, cv::Size(resizedWidth, resizedHeight));
}

void rotateWearable(cv::InputArray src, cv::OutputArray dst, double angle, cv::Point resizedLandmark, cv::Point& rotatedLandmark) {
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

#define PI 3.14159265
double calculateAngle(full_object_detection shape) {
    int leftEyeX = (shape.part(39).x() + shape.part(36).x()) / 2;
    int leftEyeY = (shape.part(39).y() + shape.part(36).y()) / 2;

    int rightEyeX = (shape.part(45).x() + shape.part(42).x()) / 2;
    int rightEyeY = (shape.part(45).y() + shape.part(42).y()) / 2;

    double angle = - std::atan( float(rightEyeY - leftEyeY) / float(rightEyeX - leftEyeX) ) * 180.0 / PI;
    return angle;
}

cv::Point getHatLandmarksOnFace (full_object_detection shape) {
    int noseTopX = shape.part(27).x();
    int noseTopY = shape.part(27).y();

    float noseToChinHeight = shape.part(8).y() - shape.part(27).y();

    // TODO: This should be improved. remove magical number
    int faceLandmarkX = noseTopX;
    int faceLandmarkY = noseTopY - 0.6 * noseToChinHeight;

    return cv::Point(faceLandmarkX, faceLandmarkY);
}

cv::Point getBeardLandmarksOnFace (full_object_detection shape) {
    return cv::Point(shape.part(62).x(), shape.part(62).y());
}

EXPORT void amooNowroozMaker(char* inputAddress, char* outputAddress) {
    try
    {
        // This example takes in a shape model file and then a list of images to
        // process.  We will take these filenames in as command line arguments.
        // Dlib comes with example images in the examples/faces folder so give
        // those as arguments to this program.
//        if (argc == 1)
//        {
//            cout << "Call this program like this:" << endl;
//            cout << "./face_landmark_detection_ex shape_predictor_68_face_landmarks.dat faces/*.jpg" << endl;
//            cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
//            cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
//            return;
//        }

        // We need a face detector.  We will use this to get bounding boxes for
        // each face in an image.
        frontal_face_detector detector = get_frontal_face_detector();
        // And we also need a shape_predictor.  This is the tool that will predict face
        // landmark positions given an image and face bounding box.  Here we are just
        // loading the model from the shape_predictor_68_face_landmarks.dat file you gave
        // as a command line argument.
        shape_predictor sp;
        deserialize("/home/reza/samsung-face/shape_predictor_68_face_landmarks.dat") >> sp;

//        image_window win, win_faces;
        cout << "processing image " << inputAddress << endl;
        array2d<rgb_pixel> img;
        load_image(img, inputAddress);

//        img.set_size(640,640);
        // Make the image larger so we can detect small faces.
//        QElapsedTimer timer;
//        timer.start();
//        pyramid_up(img);


        // Now tell the face detector to give us a list of bounding boxes
        // around all the faces in the image.
        std::vector<rectangle> dets = detector(img);
        cout << "Number of faces detected: " << dets.size() << endl;

        // Now we will go ask the shape_predictor to tell us the pose of
        // each face we detected.
        std::vector<full_object_detection> shapes;
        for (unsigned long j = 0; j < dets.size(); ++j)
        {
            full_object_detection shape = sp(img, dets[j]);
            cout << "number of parts: "<< shape.num_parts() << endl;
            cout << "pixel position of first part:  " << shape.part(0) << endl;
            cout << "pixel position of second part: " << shape.part(1) << endl;
            // You get the idea, you can get all the face part locations if
            // you want them.  Here we just store them in shapes so we can
            // put them on the screen.
            shapes.push_back(shape);
        }
//        qDebug() << timer.elapsed();

        // Now let's view our face poses on the screen.
//        win.clear_overlay();
//        win.set_image(img);
//        win.add_overlay(render_face_detections(shapes));

        // We can also extract copies of each face that are cropped, rotated upright,
        // and scaled to a standard size as shown here:
//        dlib::array<array2d<rgb_pixel> > face_chips;
//        extract_image_chips(img, get_face_chip_details(shapes), face_chips);
//        win_faces.set_image(tile_images(face_chips));

        cout << "Hit enter to process the next image..." << endl;

//        cv::Mat frame = toMat(img);
        cv::Mat frame = cv::imread(inputAddress);

        cv::Mat hat = imread("/home/reza/samsung-face/hat.png", cv::IMREAD_UNCHANGED);
        cv::Mat beard = imread("/home/reza/samsung-face/beard.png", cv::IMREAD_UNCHANGED);
        cv::Mat out;
        frame.copyTo(out);
        for (unsigned long k = 0; k < dets.size(); ++k)
        {
            cv::Mat resized_hat, resized_beard;

            cv::Point resizedHatLandmark;
            cv::Point hatLandmark(950, 1500); // TODO: These numbers should be read from config file
            resizeWearable(hat, resized_hat, shapes[k], hatLandmark, resizedHatLandmark, 2);

            cv::Point resizedBeardLandmark;
            cv::Point beardLandmark(1200, 1800); // TODO: These numbers should be read from config file
            resizeWearable(beard, resized_beard, shapes[k], beardLandmark, resizedBeardLandmark, 2.8);

            // calculation of face angle
            double angle = calculateAngle(shapes[k]);

            // rotate resized hat and beard based on calculated angle
            cv::Mat rotated_hat, rotated_beard;
            cv::Point rotatedHatLandmark;
            rotateWearable(resized_hat, rotated_hat, angle, resizedHatLandmark, rotatedHatLandmark);
            cv::Point rotatedBeardLandmark;
            rotateWearable(resized_beard, rotated_beard, angle, resizedBeardLandmark, rotatedBeardLandmark);

            cv::Point shiftHatLandmark(rotatedHatLandmark.x - getHatLandmarksOnFace(shapes[k]).x,
                                       rotatedHatLandmark.y - getHatLandmarksOnFace(shapes[k]).y);

            cv::Point shiftBeardLandmark(rotatedBeardLandmark.x - getBeardLandmarksOnFace(shapes[k]).x,
                                       rotatedBeardLandmark.y - getBeardLandmarksOnFace(shapes[k]).y);


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

        cv::imwrite(outputAddress, out);
//        cv::imshow("", out);
//        cv::waitKey(0);

//        cin.get();
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}

}

int main(int argc, char *argv[])
{
   amooNowroozMaker(argv[1], argv[2]);
}
