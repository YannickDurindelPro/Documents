#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Function for Eye Detection
void detectAndDraw(Mat& img, CascadeClassifier& faceCascade, CascadeClassifier& eyeCascade, double scale);

int main(int argc, const char** argv)
{
    // VideoCapture class for playing video for which eyes are to be detected
    VideoCapture capture;
    Mat frame, image;

    // Predefined trained XML classifiers with facial features
    CascadeClassifier faceCascade, eyeCascade;
    double scale = 1;

    // Load classifiers from "opencv/data/haarcascades" directory
    faceCascade.load("/home/yannickdurindel/Documents/other/opencv/data/haarcascades/haarcascade_frontalface_default.xml");
    eyeCascade.load("/home/yannickdurindel/Documents/other/opencv/data/haarcascades_cuda/haarcascade_eye_tree_eyeglasses.xml");


    // Start video capturing
    capture.open(1, CAP_V4L2); // Open See3Cam webcam using V4L2 backend
    if (capture.isOpened())
    {
        // Capture frames from video and detect eyes
        cout << "Eye Detection Started...." << endl;
        while (1)
        {
            capture >> frame;
            if (frame.empty())
                break;
            Mat frame1 = frame.clone();
            detectAndDraw(frame1, faceCascade, eyeCascade, scale);
            char c = (char)waitKey(10);

            // Press q to exit from window
            if (c == 27 || c == 'q' || c == 'Q')
                break;
        }
    }
    else
        cout << "Could not open camera";

    return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& faceCascade, CascadeClassifier& eyeCascade, double scale)
{
    vector<Rect> faces, eyes;
    Mat gray, smallImg;

    cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to grayscale
    double fx = 1 / scale;

    // Resize the grayscale image
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);

    // Detect faces in the input image
    faceCascade.detectMultiScale(smallImg, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Draw rectangles around faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect face = faces[i];
        Mat faceROI = smallImg(face);

        // Detect eyes within each face region
        eyeCascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // Draw rectangles around eyes
        for (size_t j = 0; j < eyes.size(); j++)
        {
            Rect eye = eyes[j];
            Point eyeCenter(face.x + eye.x + eye.width / 2, face.y + eye.y + eye.height / 2);
            int radius = cvRound((eye.width + eye.height) * 0.25);
            circle(img, eyeCenter, radius, Scalar(255, 0, 0), 3);
        }

        // Draw rectangle around the face
        //rectangle(img, face.tl(), face.br(), Scalar(0, 255, 0), 3);
    }

    // Show the processed image with detected eyes
    imshow("Eye Detection", img);
}
