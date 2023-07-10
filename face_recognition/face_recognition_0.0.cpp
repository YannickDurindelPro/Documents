#include </usr/include/dlib-19.24/dlib/opencv.h>
#include </usr/include/dlib-19.24/dlib/image_processing/frontal_face_detector.h>
#include <opencv2/opencv.hpp>

using namespace dlib;

int main()
{
    // Load the face detector model
    frontal_face_detector detector = get_frontal_face_detector();

    // Open the default camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open the camera." << std::endl;
        return 1;
    }

    // Create a window to display the camera feed
    cv::namedWindow("Face Detection", cv::WINDOW_NORMAL);

    while (true)
    {
        // Read a frame from the camera
        cv::Mat frame;
        cap.read(frame);

        // Convert the frame to dlib format
        cv_image<bgr_pixel> dlibImage(frame);

        // Detect faces in the frame
        std::vector<rectangle> faces = detector(dlibImage);

        // Draw rectangles around the detected faces
        for (const auto& face : faces)
        {
            cv::rectangle(frame, cv::Point(face.left(), face.top()), cv::Point(face.right(), face.bottom()), cv::Scalar(0, 255, 0), 2);
        }

        // Display the result
        cv::imshow("Face Detection", frame);

        // Check for user key press
        if (cv::waitKey(1) == 27) // Press Esc to exit
            break;
    }

    // Release the camera and close the window
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
