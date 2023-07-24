#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

int main() {
    // Open the DroidCam camera
    cv::VideoCapture capture("http://192.168.1.188:4747/video");

    // Load the face detection model
    cv::CascadeClassifier faceCascade;
    faceCascade.load(cv::samples::findFile("/usr/share/opencv4/lbpcascades/lbpcascade_frontalface_improved.xml"));

    if (!capture.isOpened()) {
        std::cerr << "Failed to open the camera." << std::endl;
        return -1;
    }

    int delay = 1;  // Delay between capturing frames in milliseconds
    int count = 0;  // Counter for the captured images
    std::string name = "Ethan_Dupic";  // Setting up the user profile

    cv::namedWindow("Camera", cv::WINDOW_NORMAL);

    // Capture and save 500 images
    while (count < 500) {
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

            // Expand the face region by a factor of 1.2
            float expandFactor = 1.5;
            float expandX = faceRegion.width * expandFactor;
            float expandY = faceRegion.height * expandFactor;
            float expandXOffset = (expandX - faceRegion.width) / 2;
            float expandYOffset = (expandY - faceRegion.height) / 2;

            faceRegion.x -= expandXOffset;
            faceRegion.y -= expandYOffset;
            faceRegion.width = expandX;
            faceRegion.height = expandY;

            // Ensure the expanded region is within the frame bounds
            cv::Rect frameBounds(0, 0, frame.cols, frame.rows);
            faceRegion = faceRegion & frameBounds;

            // Extract the face region from the frame
            cv::Mat face = grayFrame(faceRegion);

            // Resize the face region to match the desired size
            cv::resize(face, face, cv::Size(500, 500));

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

