// CPP program to detect face, eyes, and mouth in a video

// Include required header files from OpenCV directory
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Function for Face, Eye, and Mouth Detection
void detectAndDraw(Mat& img, CascadeClassifier& faceCascade, CascadeClassifier& eyeCascade, CascadeClassifier& mouthCascade, CascadeClassifier& leftEarCascade, double scale);
string cascadeName, eyeCascadeName, mouthCascadeName, leftEarCascadeName;

int main(int argc, const char** argv)
{
    // VideoCapture class for playing video for which faces to be detected
    VideoCapture capture;
    Mat frame, image;

    // PreDefined trained XML classifiers with facial features
    CascadeClassifier faceCascade, eyeCascade, mouthCascade, leftEarCascade;
    double scale = 1;

    // Load classifiers from "opencv/data/haarcascades" directory
    eyeCascade.load("/usr/include/opencv4/opencv2/haarcascades/haarcascade_eye_tree_eyeglasses.xml");
    mouthCascade.load("/usr/include/opencv4/opencv2/haarcascades/haarcascades_mcs_mouth.xml"); // Replace with the correct path to the mouth cascade XML file
    faceCascade.load("/usr/include/opencv4/opencv2/haarcascades/haarcascade_frontalcatface.xml");
    leftEarCascade.load("/usr/include/opencv4/opencv2/haarcascades/haarcascades_mcs_leftear.xml");

    // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
    capture.open(0);
    if (capture.isOpened())
    {
        // Capture frames from video and detect faces, eyes, and mouth
        cout << "Face, Eye, Ear, and Mouth Detection Started...." << endl;
        while (1)
        {
            capture >> frame;
            if (frame.empty())
                break;
            Mat frame1 = frame.clone();
            detectAndDraw(frame1, faceCascade, eyeCascade, mouthCascade, leftEarCascade, scale);
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

void detectAndDraw(Mat& img, CascadeClassifier& faceCascade, CascadeClassifier& eyeCascade, CascadeClassifier& mouthCascade, CascadeClassifier& leftEarCascade, double scale)
{
    vector<Rect> faces;
    Mat gray, smallImg;

    cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale
    double fx = 1 / scale;

    // Resize the Grayscale Image
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);
    double brightness = 150; // Adjust this value as needed
    Mat brightImg = smallImg + Scalar(brightness, brightness, brightness);

    // Detect faces of different sizes using cascade classifier
    faceCascade.detectMultiScale(brightImg, faces, 1.05, 3, 0 | CASCADE_SCALE_IMAGE, Size(80, 80));

    // Draw rectangles around the faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
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

        if (eyeCascade.empty() || mouthCascade.empty())
            continue;
        smallImgROI = smallImg(r);

        // Detection of eyes in the input image
        eyeCascade.detectMultiScale(smallImgROI, nestedObjects, 1.3, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // Draw rectangles around eyes
        for (size_t j = 0; j < nestedObjects.size(); j++)
        {
            Rect nr = nestedObjects[j];
            Rect eyeRect(cvRound((r.x + nr.x) * scale), cvRound((r.y + nr.y) * scale), cvRound(nr.width * scale), cvRound(nr.height * scale));
            rectangle(img, eyeRect, color, 3, 8, 0);
            imwrite("eye.jpg", img);
        }

        // Detection of mouth in the input image
        vector<Rect> mouthObjects;
        mouthCascade.detectMultiScale(smallImgROI, mouthObjects, 1.3, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // Draw rectangles around mouth
        for (size_t j = 0; j < mouthObjects.size(); j++)
        {
            Rect nr = mouthObjects[j];
            Rect mouthRect(cvRound((r.x + nr.x) * scale), cvRound((r.y + nr.y) * scale), cvRound(nr.width * scale), cvRound(nr.height * scale));
            rectangle(img, mouthRect, Scalar(0, 255, 0), 3, 8, 0);
            imwrite("mouth.jpg", img);
        }

        // Detection of left ear in the input image
        vector<Rect> leftEarObjects;
        leftEarCascade.detectMultiScale(smallImgROI, leftEarObjects, 1.3, 5, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // Draw rectangles around left ear
        for (size_t j = 0; j < leftEarObjects.size(); j++)
        {
            Rect nr = leftEarObjects[j];
            Rect leftEarRect(cvRound((r.x + nr.x) * scale), cvRound((r.y + nr.y) * scale), cvRound(nr.width * scale), cvRound(nr.height * scale));
            rectangle(img, leftEarRect, Scalar(120, 120, 120), 3, 8, 0);
            imwrite("leftEar.jpg", img);
        }
    }

    // Show processed image with detected faces, eyes, and mouth
    imshow("Face, Eye, and Mouth Detection", img);
}
