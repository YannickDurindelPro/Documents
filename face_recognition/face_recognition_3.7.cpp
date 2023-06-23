#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <filesystem>

int main() {
    // Load the face recognition model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->read("/home/yannickdurindel/Documents/face_recognition/model.xml");
    int result = 0;
    int counter = 0;
    int detect = 0;

    // Load the face detection model
    cv::CascadeClassifier faceCascade;
    faceCascade.load("/home/yannickdurindel/Documents/other/opencv/data/lbpcascades/lbpcascade_frontalface_improved.xml");

    // Specify the base folder containing the images
    std::string baseFolderPath = "/home/yannickdurindel/Documents/face_recognition/dataset/other/backup/";

    // Define the labels and corresponding person names
    std::vector<int> labels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<std::string> personNames = {
        "Frederic_Aubert", "Jean-Pierre_Stang", "Jules_Gregoire", "Neyl_Boukerche", "Pascal_Chevallier", "Alexandre_Goudeau", "Jerome_Pauc1",
        "Evgeunii_Dombrovskii", "Ilia_Seliverstov", "Stephane_Grange", "Yannick_Durindel", "Nicolas_Hourcastagnou1"
        };

    // Iterate over person names
    for (const std::string& personName : personNames) {
        std::string folderPath = baseFolderPath + personName + "/";
        int label = std::distance(personNames.begin(), std::find(personNames.begin(), personNames.end(), personName));

        // Iterate over images in the folder
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            // Load the image
            cv::Mat frame = cv::imread(entry.path().string());
            counter++;

            // Convert the frame to grayscale
            cv::Mat grayFrame;
            cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

            // Detect faces in the frame
            std::vector<cv::Rect> faces;
            faceCascade.detectMultiScale(grayFrame, faces);

            // Perform face recognition on the detected faces
            for (const auto& face : faces) {
                // Resize the face region to match the model's input size
                cv::Mat faceROI = grayFrame(face);
                cv::Mat resizedFace;
                cv::resize(faceROI, resizedFace, cv::Size(100, 100));
                detect++;

                // Predict the label of the face
                int predictedLabel = -1;
                double confidence = 0.0;
                model->predict(resizedFace, predictedLabel, confidence);
                std::cout << "Predicted Label: " << predictedLabel << std::endl;

                if (predictedLabel == label) {
                    result++;
                    //std::cout << result << std::endl;
                }

                cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);

                // Check if the predicted label matches the ground truth label
                if (predictedLabel == label) {
                    // Draw a green rectangle around the face
                    cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
                } else {
                    // Draw a red rectangle around the face
                    cv::rectangle(frame, face, cv::Scalar(0, 0, 255), 2);
                }
            }

            // Display the frame
            cv::imshow("Face Recognition", frame);
            cv::waitKey(10);
        }
    }

    // Print the recognition accuracy
    double accuracy = static_cast<double>(result) / counter * 100;
    std::cout << "Accuracy: " << accuracy << "%" << std::endl;
    std::cout << "Detected: " << detect << std::endl;
    return 0;
}
