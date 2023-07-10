#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

int main() {
    // Load the face recognition model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->read("/home/yannickdurindel/Documents/face_recognition/model.xml");

    // Load the face detection model
    cv::CascadeClassifier faceCascade;
    faceCascade.load("/home/yannickdurindel/Documents/other/opencv/data/haarcascades/haarcascade_frontalface_default.xml");

    // Initialize the camera
    cv::VideoCapture camera(0);  // Change the argument to the appropriate camera index if needed
    if (!camera.isOpened()) {
        std::cerr << "Failed to open the camera." << std::endl;
        return 1;
    }

    // Read the profile image
    cv::Mat profileImage = cv::imread("/home/yannickdurindel/Documents/face_recognition/test-model/yannick_training.jpg", cv::IMREAD_GRAYSCALE);

    // Train the face recognition model with the profile image
    std::vector<cv::Mat> profileImages = { profileImage };
    std::vector<int> profileLabels = { 0 };
    model->train(profileImages, profileLabels);

    while (true) {
        // Capture a frame from the camera
        cv::Mat frame;
        camera.read(frame);

        // Convert the frame to grayscale
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Detect faces in the frame
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(grayFrame, faces);

        // Perform face recognition on the detected faces
        for (const auto& face : faces) {
            // Resize the face region to match the profile image size
            cv::Mat faceROI = grayFrame(face);
            cv::resize(faceROI, faceROI, profileImage.size());

            // Predict the label of the face
            int predictedLabel = -1;
            double confidence = 0.0;
            model->predict(faceROI, predictedLabel, confidence);

            // Check if the predicted label matches the profile label
            if (predictedLabel == 0) {
                cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
                cv::putText(frame, "Yannick Durindel", cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
                cv::imwrite("yannickdurindel.jpg",frame);
            } else {
                cv::rectangle(frame, face, cv::Scalar(0, 0, 255), 2);
            }
        }

        cv::imshow("Face Recognition", frame);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    camera.release();

    return 0;
}
