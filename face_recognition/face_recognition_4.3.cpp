#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <filesystem>
#include <omp.h>

int main() {
    // Load the face recognition model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->read("/home/yannickdurindel/Documents/face_recognition/model0.xml");

    // Load the face detection model
    cv::CascadeClassifier faceCascade;
    faceCascade.load("/home/yannickdurindel/Documents/other/opencv/data/lbpcascades/lbpcascade_frontalface_improved.xml");

    // Specify the base folder containing the images
    std::string baseFolderPath = "/home/yannickdurindel/Documents/face_recognition/dataset/test_dataset/";

    // Define the labels and corresponding person names
    std::vector<int> labels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<std::string> personNames = {
        "Frederic_Aubert", "Jean-Pierre_Stang", "Jules_Gregoire", "Neyl_Boukerche", "Pascal_Chevallier", "Alexandre_Goudeau", "Jerome_Pauc1",
        "Evgeunii_Dombrovskii", "Ilia_Seliverstov", "Stephane_Grange", "Yannick_Durindel", "Nicolas_Hourcastagnou1"
    };

    // Iterate over person names
    for (const std::string& personName : personNames) {
        int result = 0;
        int counter = 0;
        int detect = 0;

        std::string folderPath = baseFolderPath + personName + "/";
        int label = std::distance(personNames.begin(), std::find(personNames.begin(), personNames.end(), personName));

        // Prepare a vector to hold detected faces and resized faces
        std::vector<cv::Mat> detectedFaces;
        std::vector<cv::Mat> resizedFaces;

        // Iterate over images in the folder
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            counter++;
            // Load the image
            cv::Mat frame = cv::imread(entry.path().string());

            // Convert the frame to grayscale
            cv::Mat grayFrame;
            cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

            // Detect faces in the frame
            std::vector<cv::Rect> faces;
            faceCascade.detectMultiScale(grayFrame, faces);

            // Collect detected faces and resize them
            for (const auto& face : faces) {
                cv::Mat faceROI = grayFrame(face);
                cv::Mat resizedFace;
                cv::resize(faceROI, resizedFace, cv::Size(100, 100));
                detect++;

                detectedFaces.push_back(faceROI);
                resizedFaces.push_back(resizedFace);
            }
        }

        // Perform face recognition on the detected faces in parallel
        #pragma omp parallel for reduction(+:result)
        for (int i = 0; i < detectedFaces.size(); i++) {
            int predictedLabel = -1;
            double confidence = 0.0;
            model->predict(resizedFaces[i], predictedLabel, confidence);

            if (predictedLabel == label) {
                result++;
            }
        }

        // Print the recognition accuracy for the current person
        double accuracy = static_cast<double>(result) / detect * 100;
        std::cout << "Accuracy for " << personName << ": " << accuracy << "%" << std::endl;
        std::cout << "Detection for " << personName << ": " << 100 * detect / counter << "% \n" << std::endl;
    }

    return 0;
}
