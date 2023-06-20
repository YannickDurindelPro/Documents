#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

int main() {
    // Define the path to the directory containing the dataset images
    std::string datasetRootPath = "/home/yannickdurindel/Documents/face_recognition/dataset/train-dataset/";

    // Vector to store image paths
    std::vector<std::string> imagePaths;

    // Read the dataset and labels
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    // Initialize the label counter
    int labelCounter = 0;

    // Iterate over folders in the dataset root directory
    for (const auto& personDir : fs::directory_iterator(datasetRootPath)) {
        if (!personDir.is_directory()) {
            continue;
        }

        std::string personName = personDir.path().filename().string();
        std::cout << "Training for person: " << personName << std::endl;

        // Iterate over files in the person's directory
        for (const auto& entry : fs::directory_iterator(personDir.path())) {
            if (entry.is_regular_file()) {
                imagePaths.push_back(entry.path().string());
            }
        }

        // Loop through the image paths
        for (const std::string& imagePath : imagePaths) {
            cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

            if (image.empty()) {
                std::cerr << "Failed to read image: " << imagePath << std::endl;
                continue;
            }

            // Resize the image to a consistent size (e.g., 100x100)
            //cv::resize(image, image, cv::Size(100, 100));

            // Add the image and corresponding label to the vectors
            images.push_back(image);
            labels.push_back(labelCounter);  // Assign incremental labels for training

            //std::cout << "Added image: " << imagePath << std::endl;
        }

        // Increment the label counter for the next person
        labelCounter++;

        // Clear imagePaths for the next person
        imagePaths.clear();
    }

    // Create and train the LBPHFaceRecognizer model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create(1,8, 4, 4, 80.0);
    model->train(images, labels);

    // Save the trained model
    std::string modelPath = "model.xml";
    model->save(modelPath);

    return 0;
}
