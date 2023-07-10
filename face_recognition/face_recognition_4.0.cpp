#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>
#include <iostream>

int main() {
    // Load the trained model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->read("/home/yannickdurindel/Documents/face_recognition/model.xml");

    // Open the camera
    cv::VideoCapture cap(1);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open the camera." << std::endl;
        return 1;
    }

    cv::Mat frame;
    cv::namedWindow("Face Recognition", cv::WINDOW_NORMAL);

    while (true) {
        // Capture frame from the camera
        cap >> frame;

        // Convert the frame to grayscale
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Perform face detection on the grayscale frame
        std::vector<cv::Rect> faces;
        cv::CascadeClassifier faceCascade;
        faceCascade.load("/home/yannickdurindel/Documents/other/opencv/data/lbpcascades/lbpcascade_frontalface_improved.xml");
        faceCascade.detectMultiScale(grayFrame, faces);

        // Iterate over detected faces
        for (const cv::Rect& face : faces) {
            // Extract the region of interest (face) from the frame
            cv::Mat faceROI = grayFrame(face);

            // Resize the face region to the same size as training images
            cv::resize(faceROI, faceROI, cv::Size(500, 500));

            // Perform face recognition on the face region
            int predictedLabel = -1;
            double confidence = 0.0;
            model->predict(faceROI, predictedLabel, confidence);

            // Draw a rectangle around the face
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);

            // Display the predicted label and confidence on the frame
            std::string label = "Label: " + std::to_string(predictedLabel);
            std::string conf = "Confidence: " + std::to_string(confidence);
            cv::putText(frame, label, cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, conf, cv::Point(face.x, face.y + face.height + 20), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
        }

        // Display the frame
        cv::imshow("Face Recognition", frame);

        // Check for the 'Esc' key press
        if (cv::waitKey(1) == 27)
            break;
    }

    // Release the camera and destroy the windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
