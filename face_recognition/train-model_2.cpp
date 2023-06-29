#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

const int IMG_WIDTH = 100;
const int IMG_HEIGHT = 100;

void loadTrainingData(const std::string& folderPath, std::vector<cv::Mat>& images, std::vector<int>& labels) {
    cv::Mat image;
    int label = 0;

    // Load images from each subfolder
    cv::glob(folderPath + "/*", images, false);

    for (const auto& folder : images) {
        cv::String className = folder.substr(folder.find_last_of('/') + 1);

        // Load images from the current class folder
        std::vector<cv::String> files;
        cv::glob(folder + "/*.jpg", files, false);

        for (const auto& file : files) {
            // Read the image and resize it to a fixed size
            image = cv::imread(file, cv::IMREAD_GRAYSCALE);
            cv::resize(image, image, cv::Size(IMG_WIDTH, IMG_HEIGHT));

            // Add the image and its corresponding label to the training data
            images.push_back(image);
            labels.push_back(label);
        }

        label++;
    }
}

int main() {
    // Path to the training dataset folder
    std::string datasetPath = "/home/yannickdurindel/Documents/face_recognition/dataset/train-dataset";

    // Vector to store training images and labels
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    // Load the training data
    loadTrainingData(datasetPath, images, labels);

    // Create the face recognition model
    cv::Ptr<cv::face::FaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();

    // Train the model with the loaded data
    model->train(images, labels);

    // Save the trained model to a file
    model->save("/path/to/trained_model.xml");

    return 0;
}
