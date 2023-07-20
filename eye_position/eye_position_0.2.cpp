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
        cv::Mat frame;
        cap.read(frame);

        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> eyes;
        eyeCascade.detectMultiScale(grayFrame, eyes, 1.1, 3);

        for (const cv::Rect& eyeRect : eyes) {
            cv::Mat eyeROI = grayFrame(eyeRect);

            cv::Mat thresholded;
            cv::threshold(eyeROI, thresholded, 50, 255, cv::THRESH_BINARY_INV);

            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(thresholded, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

            if (!contours.empty()) {
                cv::Mat contourImage = cv::Mat::zeros(thresholded.size(), CV_8UC3);
                cv::drawContours(contourImage, contours, -1, cv::Scalar(0, 255, 0), 2);

                std::vector<cv::Point> largestContour = contours[0];
                cv::Rect boundingRect = cv::boundingRect(largestContour);
                cv::Point center(boundingRect.x + boundingRect.width / 2, boundingRect.y + boundingRect.height / 2);

                cv::circle(frame, eyeRect.tl() + center, 2, cv::Scalar(0, 0, 255), -1);
            }
        }

        cv::imshow("Pupil Tracking", frame);

        if (cv::waitKey(1) == 27)  // Break the loop if the 'Esc' key is pressed
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
