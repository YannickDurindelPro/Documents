#include <opencv2/opencv.hpp>

int main() {
    // Create a VideoCapture object and open the DroidCam camera
    cv::VideoCapture cap("http://192.168.1.139:4747/video");

    // Check if the camera is opened successfully
    if (!cap.isOpened()) {
        std::cout << "Failed to connect to the DroidCam camera!" << std::endl;
        return -1;
    }

    // Main loop to continuously read frames from the camera
    while (true) {
        cv::Mat frame;

        // Read a frame from the camera
        if (!cap.read(frame)) {
            std::cout << "Failed to read frame from the camera!" << std::endl;
            break;
        }

        // Display the frame
        cv::imshow("Camera", frame);

        // Exit the loop if the 'Esc' key is pressed
        if (cv::waitKey(1) == 27)
            break;
    }

    // Release the VideoCapture object and close the window
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
