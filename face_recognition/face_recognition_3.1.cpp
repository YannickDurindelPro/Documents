#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

using namespace cv;

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
    std::vector<int> profileLabels = { brightImg0 };
    model->train(profileImages, profileLabels);

    // Read and process the image to be tested
    cv::Mat testImage = cv::imread("/home/yannickdurindel//Documents/face_recognition/test-model/image_test.jpg", cv::IMREAD_GRAYSCALE);

    // Detect faces in the test image
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(testImage, faces);

    // Detect faces of different sizes using cascade classifier
    faceCascade.detectMultiScale(brightImg, faces, 1.05, 3, 0 | CASCADE_SCALE_IMAGE, Size(80, 80));

    // Draw rectangles around the faces
    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool

        double aspect_ratio = (double)r.width / r.height;
        if (0.75 < aspect_ratio && aspect_ratio < 1.3)
        {
            Rect faceRect(cvRound(r.x * scale), cvRound(r.y * scale), cvRound(r.width * scale), cvRound(r.height * scale));
            rectangle(img, faceRect, Scalar(0, 0, 0), 3, 8, 0);
            //imwrite("face.jpg", img);
        }
        else
            rectangle(img, Point(cvRound(r.x * scale), cvRound(r.y * scale)), Point(cvRound((r.x + r.width - 1) * scale), cvRound((r.y + r.height - 1) * scale)), Scalar(255, 0, 0), 3, 8, 0);
            //imwrite("facebis.jpg", img);

        if (eyeCascade.empty() || mouthCascade.empty())
            continue;
        smallImgROI = smallImg(r);
    }

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