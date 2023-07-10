#include <opencv2/opencv.hpp>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>

using namespace cv;
using namespace dlib;

int main()
{
    // Load the face detector and landmark predictor models from dlib
    frontal_face_detector faceDetector = get_frontal_face_detector();
    shape_predictor landmarkPredictor;
    deserialize("path_to_landmark_model.dat") >> landmarkPredictor;

    // Open the video stream or read frames from a video file
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Failed to open the video stream." << std::endl;
        return -1;
    }

    // Loop over the video frames
    while (true)
    {
        Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        // Convert the frame to dlib's image format
        cv_image<bgr_pixel> dlibImg(frame);

        // Detect faces in the frame
        std::vector<rectangle> faces = faceDetector(dlibImg);

        // Loop over the detected faces
        for (const rectangle& face : faces)
        {
            // Detect landmarks within each face
            full_object_detection landmarks = landmarkPredictor(dlibImg, face);

            // Extract the eye landmarks
            point leftEye = landmarks.part(LEFT_EYE_LANDMARK_INDEX);
            point rightEye = landmarks.part(RIGHT_EYE_LANDMARK_INDEX);

            // Calculate the gaze direction based on the eye landmarks
            // Perform your own gaze estimation algorithm here

            // Draw circles around the eyes and display the frame
            circle(frame, cv::Point(leftEye.x(), leftEye.y()), 2, Scalar(0, 255, 0), -1);
            circle(frame, cv::Point(rightEye.x(), rightEye.y()), 2, Scalar(0, 255, 0), -1);
        }

        // Display the frame
        imshow("Gaze Estimation", frame);

        // Exit if 'q' is pressed
        if (waitKey(1) == 'q')
            break;
    }

    // Release the video capture and destroy the windows
    cap.release();
    destroyAllWindows();

    return 0;
}
