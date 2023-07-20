#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main() {
    cv::CascadeClassifier eyeCascade;
    eyeCascade.load("/home/yannickdurindel/Documents/other/opencv/data/haarcascades_cuda/haarcascade_eye_tree_eyeglasses.xml");

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Failed to open the video capture device." << std::endl;
        return -1;
    }

    while (true) {
        // Read a frame from the video capture
        cv::Mat frame;
        cap.read(frame);

        // Convert the frame to grayscale for eye detection
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Detect eyes using the Haar cascade classifier
        std::vector<cv::Rect> eyes;
        eyeCascade.detectMultiScale(grayFrame, eyes, 1.1, 3);

        for (const cv::Rect& eyeRect : eyes) {
            // Extract the region of interest (ROI) for the detected eye
            cv::Mat eyeROI = grayFrame(eyeRect);
            cv::Mat eyeColor = frame(eyeRect);

            // Threshold the ROI to enhance the pupil
            cv::Mat thresholded;
            cv::threshold(eyeROI, thresholded, 50, 255, cv::THRESH_BINARY_INV);

            // Find contours in the thresholded image
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(thresholded, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

            if (!contours.empty()) {
                // Find the largest contour (presumed to be the pupil)
                std::vector<cv::Point> largestContour = contours[0];
                cv::Rect boundingRect = cv::boundingRect(largestContour);
                cv::Point pupilCenter(boundingRect.x + boundingRect.width / 2, boundingRect.y + boundingRect.height / 2);

                // Calculate the coordinates of the pupil relative to the original frame
                cv::Point pupilCoordinates(pupilCenter.x + eyeRect.x, pupilCenter.y + eyeRect.y);

                // Calculate the coordinates of the center of the eye rectangle
                cv::Point eyeCenter(eyeRect.x + eyeRect.width / 2, eyeRect.y + eyeRect.height / 2);

                // Draw a circle at the pupil center to visualize the tracking
                cv::circle(eyeColor, pupilCenter, 2, cv::Scalar(0, 0, 255), -1);

                // Print the distance between the eye center and the pupil center
                std::cout << "Eye distance to the front: " << round(sqrt(pow((eyeCenter.x - pupilCoordinates.x),2) + pow((eyeCenter.y - pupilCoordinates.y),2))) << std::endl;
            }

            // Draw a rectangle around the detected eye
            cv::rectangle(frame, eyeRect, cv::Scalar(255, 0, 0), 2);
        }

        // Display the frame with eye detection and pupil tracking
        cv::imshow("Eye Detection and Pupil Tracking", frame);

        // Break the loop if the 'Esc' key is pressed
        if (cv::waitKey(1) == 27)
            break;
    }

    // Release the video capture and destroy the windows
    cap.release();
    cv::destroyAllWindows();
    return 0;
    }