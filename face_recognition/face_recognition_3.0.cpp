#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

int main() {
    // Load the face recognition model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->read("/home/yannickdurindel/Documents/face_recognition/model.xml");

    // Load the face detection model
    cv::CascadeClassifier faceCascade;
    faceCascade.load("/home/yannickdurindel/Documents/other/opencv/data/haarcascades/haarcascade_frontalface_default.xml");

    // Read the profile image
    cv::Mat profileImage = cv::imread("/home/yannickdurindel//Documents/face_recognition/test-model/image_training.jpg", cv::IMREAD_GRAYSCALE);

    // Train the face recognition model with the profile image
    std::vector<cv::Mat> profileImages = { profileImage };
    std::vector<int> profileLabels = { 0 };
    model->train(profileImages, profileLabels);

    // Read and process the image to be tested
    cv::Mat testImage = cv::imread("/home/yannickdurindel//Documents/face_recognition/test-model/image_test.jpg", cv::IMREAD_GRAYSCALE);

    // Detect faces in the test image
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(testImage, faces);

    // Perform face recognition on the detected faces
    for (const auto& face : faces) {
        // Resize the face region to match the profile image size
        cv::Mat faceROI = testImage(face);
        cv::resize(faceROI, faceROI, profileImage.size());

        // Predict the label of the face
        int predictedLabel = -1;
        double confidence = 0.0;
        model->predict(faceROI, predictedLabel, confidence);

        // Check if the predicted label matches the profile label
        if (predictedLabel == 0) {
            // It's a match
            cv::rectangle(testImage, face, cv::Scalar(0, 255, 0), 2);
            cv::putText(testImage, "Match", cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
        } else {
            // It's not a match
            cv::rectangle(testImage, face, cv::Scalar(0, 0, 255), 2);
            cv::putText(testImage, "Not a Match", cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 0, 255), 2);
        }
    }

    // Display the result
    cv::imshow("Face Recognition", testImage);
    cv::waitKey(0);

    return 0;
}