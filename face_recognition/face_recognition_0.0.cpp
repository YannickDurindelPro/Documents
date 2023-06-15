// CPP program to detect face in a video

// Include required header files from OpenCV directory
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Function for Face, Eye, and Mouth Detection
void detectAndDraw(Mat& img, CascadeClassifier& faceCascade, double scale);
string cascadeName;

int main(int argc, const char** argv)
{
    // VideoCapture class for playing video for which faces to be detected
    VideoCapture capture;
    Mat frame, image;

    // PreDefined trained XML classifiers with facial features
    CascadeClassifier faceCascade;
    double scale = 1;

    // Load classifiers from "opencv/data/haarcascades" directory
    faceCascade.load("/usr/include/opencv4/opencv2/haarcascades/haarcascade_frontalcatface.xml");

    // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
    capture.open(0);
    if (capture.isOpened())
    {
        // Capture frames from video and detect faces, eyes, and mouth
        cout << "Face Detection Started...." << endl;
        while (1)
        {
            capture >> frame;
            if (frame.empty())
                break;
            Mat frame1 = frame.clone();
            detectAndDraw(frame1, faceCascade, scale);
            char c = (char)waitKey(10);

            // Press q to exit from window
            if (c == 27 || c == 'q' || c == 'Q')
                break;
        }
    }
    else
        cout << "Could not Open Camera";
    return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& faceCascade, double scale)
{
    vector<Rect> faces;
    Mat gray, smallImg;

    cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale
    double fx = 1 / scale;

    // Resize the Grayscale Image
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);
    double brightness = 0; // Adjust this value as needed
    Mat brightImg = smallImg + Scalar(brightness, brightness, brightness);

    // Detect faces of different sizes using cascade classifier
    faceCascade.detectMultiScale(brightImg, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(80, 80));

    // Draw rectangles around the faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        Point center;
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool

        double aspect_ratio = (double)r.width / r.height;
        if (0.75 < aspect_ratio && aspect_ratio < 1.3)
        {
            Rect faceRect(cvRound(r.x * scale), cvRound(r.y * scale), cvRound(r.width * scale), cvRound(r.height * scale));
            rectangle(img, faceRect, Scalar(0, 0, 0), 3, 8, 0);
            imwrite("face.jpg", img);
        }
        else
            rectangle(img, Point(cvRound(r.x * scale), cvRound(r.y * scale)), Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), Scalar(255, 0, 0), 3, 8, 0);
            imwrite("facebis.jpg", img);
    }

    // Show processed image with detected faces, eyes, and mouth
    imshow("Face, Eye, and Mouth Detection", img);
}