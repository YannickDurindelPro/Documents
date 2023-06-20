#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

int main() {
    cv::VideoCapture capture(0);  // Open the default camera (index 0)

    // Load the face detection model
    cv::CascadeClassifier faceCascade;
    faceCascade.load(cv::samples::findFile("/home/yannickdurindel/Documents/other/opencv/data/lbpcascades/lbpcascade_frontalface_improved.xml"));

    if (!capture.isOpened()) {
        std::cerr << "Failed to open the camera." << std::endl;
        return -1;
    }

    int delay = 1;  // Delay between capturing frames in milliseconds
    int count = 0;  // Counter for the captured images
    std::string name = "Yannick_Durindel";    // Setting up the user profile

    cv::namedWindow("Camera", cv::WINDOW_NORMAL);

    // Capture and save 100 images
    while (count < 100) {
        cv::Mat frame;
        capture.read(frame);  // Capture a frame from the camera

        if (frame.empty()) {
            std::cerr << "Failed to capture a frame." << std::endl;
            return -1;
        }

        // Convert the frame to grayscale
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Detect faces in the frame
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(grayFrame, faces);

        if (!faces.empty()) {
            // Get the largest face region
            cv::Rect faceRegion = faces[0];

            // Extract the face region from the frame
            cv::Mat face = grayFrame(faceRegion);

            // Resize the face region to match the desired size
            cv::resize(face, face, cv::Size(100, 100));

            cv::imshow("Camera", face);  // Display the captured face region

            std::stringstream filename;
            filename << name << count << ".jpg";
            cv::imwrite("dataset/train-dataset/" + name + "/" + filename.str(), face);  // Save the captured face region as an image

            count++;
        }

        cv::waitKey(delay);  // Wait for a specified delay
    }

    capture.release();  // Release the camera

    return 0;
}
