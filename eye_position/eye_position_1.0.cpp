#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include </usr/include/dlib-19.24/dlib/opencv.h>
#include </usr/include/dlib-19.24/dlib/image_processing.h>
#include </usr/include/dlib-19.24/dlib/image_processing/frontal_face_detector.h>

int main() {
    dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
    dlib::shape_predictor landmarkDetector;
    dlib::deserialize("/usr/include/dlib-19.24/dlib/shape_predictor_68_face_landmarks.dat") >> landmarkDetector;

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

        dlib::cv_image<unsigned char> dlibImage(grayFrame);

        std::vector<dlib::rectangle> faces = faceDetector(dlibImage);

        for (const dlib::rectangle& face : faces) {
            dlib::full_object_detection landmarks = landmarkDetector(dlibImage, face);

            // Extract eye landmarks
            dlib::point leftEye = landmarks.part(36);
            dlib::point rightEye = landmarks.part(45);

            // Convert dlib points to OpenCV points
            cv::Point leftEyePoint(leftEye.x(), leftEye.y());
            cv::Point rightEyePoint(rightEye.x(), rightEye.y());

            // Draw eye rectangles
            cv::Rect leftEyeRect(leftEyePoint.x - 10, leftEyePoint.y - 10, 20, 20);
            cv::Rect rightEyeRect(rightEyePoint.x - 10, rightEyePoint.y - 10, 20, 20);
            cv::rectangle(frame, leftEyeRect, cv::Scalar(255, 0, 0), 2);
            cv::rectangle(frame, rightEyeRect, cv::Scalar(255, 0, 0), 2);

            // Draw pupil centers
            cv::Point leftPupilCenter(leftEyePoint.x + 10, leftEyePoint.y + 10);
            cv::Point rightPupilCenter(rightEyePoint.x + 10, rightEyePoint.y + 10);
            cv::circle(frame, leftPupilCenter, 2, cv::Scalar(0, 0, 255), -1);
            cv::circle(frame, rightPupilCenter, 2, cv::Scalar(0, 0, 255), -1);

            // Print coordinates
            std::cout << "Left eye center: (" << leftPupilCenter.x << ", " << leftPupilCenter.y << ")" << std::endl;
            std::cout << "Right eye center: (" << rightPupilCenter.x << ", " << rightPupilCenter.y << ")" << std::endl;
        }

        cv::imshow("Eye Detection and Pupil Tracking", frame);

        if (cv::waitKey(1) == 27)  // Break the loop if the 'Esc' key is pressed
            break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
