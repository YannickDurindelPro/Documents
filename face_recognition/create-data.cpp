#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

int main() {
    cv::VideoCapture capture(0);  // Open the default camera (index 0)

    if (!capture.isOpened()) {
        std::cerr << "Failed to open the camera." << std::endl;
        return -1;
    }

    int delay = 100;  // Delay between capturing frames in milliseconds
    int count = 300;  // Counter for the captured images

    cv::namedWindow("Camera", cv::WINDOW_NORMAL);

    // Capture and save 100 images
    for (int i = 0; i < 100; i++) {
        cv::Mat frame;
        capture.read(frame);  // Capture a frame from the camera

        if (frame.empty()) {
            std::cerr << "Failed to capture a frame." << std::endl;
            return -1;
        }

        cv::imshow("Camera", frame);  // Display the captured frame

        std::stringstream filename;
        filename << "yannick_" << count << ".jpg";
        cv::imwrite("dataset/train-dataset/me/" + filename.str(), frame);  // Save the captured frame as an image

        count++;

        cv::waitKey(delay);  // Wait for a specified delay
    }

    capture.release();  // Release the camera

    return 0;
}
