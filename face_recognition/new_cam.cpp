#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(1); // Open the default camera (change the index if you have multiple cameras)

    if (!cap.isOpened()) {
        std::cout << "Failed to open the camera" << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame;
        cap.read(frame); // Read a frame from the camera

        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            break;
        }

        cv::imshow("Camera", frame); // Display the frame

        if (cv::waitKey(1) == 27) // Exit if ESC is pressed
            break;
    }

    cap.release(); // Release the camera
    cv::destroyAllWindows(); // Close all windows

    return 0;
}
