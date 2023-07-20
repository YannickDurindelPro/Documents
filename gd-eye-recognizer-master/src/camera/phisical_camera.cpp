#include "phisical_camera.hpp"

namespace EyeLights { namespace EyeRecognizer {
    using namespace godot;
    using namespace std;
    using namespace cv;

    PhisicalCamera::PhisicalCamera() {
        image.instantiate();
        texture.instantiate();
    }

    PhisicalCamera::~PhisicalCamera() {

    }

    void PhisicalCamera::_bind_methods() {
        std::cout << "PhisicalCamera::_bind_methods()" << std::endl;
        ClassDB::bind_method(D_METHOD("open"), &PhisicalCamera::open);
        ClassDB::bind_method(D_METHOD("show"), &PhisicalCamera::_process);
    }

    bool PhisicalCamera::open(int cameraId) {
        cv::VideoCapture cap(cameraId); // Open the default camera (usually the first camera available)

        if (!cap.isOpened()) {
            std::cout << "Error: Could not open the camera.\n";
            return 0;
        }

        cv::namedWindow("Camera Feed", cv::WINDOW_NORMAL); // Create a window to display the camera feed

        while (true) {
            cv::Mat frame;
            cap >> frame; // Capture a frame from the camera

            if (frame.empty()) {
                std::cout << "Error: Failed to capture frame.\n";
                break;
            }

            cv::imshow("Camera Feed", frame); // Display the frame in the window

            char key = cv::waitKey(1); // Wait for a key press (1ms delay)
            if (key == 27) { // If the 'Esc' key is pressed, break the loop
                break;
            }
        }

        cap.release(); // Release the camera
        cv::destroyAllWindows(); // Close all OpenCV windows
        return 0;
    }


    void PhisicalCamera::_process(double delta) {
        if (isOpened) {
            cap >> currentFrame;
            if (!currentFrame.empty()) {
                cv::imshow("Camera", currentFrame);
                cv::waitKey(1);
            }
        }
    }

    void PhisicalCamera::shutdown() {
        cv::destroyWindow("Camera");
    }

}}
