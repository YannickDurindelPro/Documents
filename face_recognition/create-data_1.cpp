#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>

int main() {
    std::string folderPath = "/home/yannickdurindel/Documents/face_recognition/dataset/train-dataset/Thibault_Aglioni/"; // Path to the folder containing the images
    int count = 0;  // Counter for the captured images
    std::string name = "Jerome_Pauc";  // Setting up the user profile

    // Get the list of image files in the folder
    std::vector<cv::String> imageFiles;
    cv::glob(folderPath, imageFiles);

    if (imageFiles.empty()) {
        std::cerr << "No image files found in the folder." << std::endl;
        return -1;
    }

    cv::namedWindow("Camera", cv::WINDOW_NORMAL);

    // Process each image in the folder
    for (const auto& imagePath : imageFiles) {
        // Load the image
        cv::Mat frame = cv::imread(imagePath);

        if (frame.empty()) {
            std::cerr << "Failed to load image: " << imagePath << std::endl;
            return -1;
        }

        cv::imshow("Camera", frame);  // Display the captured image

        std::stringstream filename;
        filename << name << count << ".jpg";
        cv::imwrite("dataset/train-dataset/" + name + "/" + filename.str(), frame);  // Save the captured image

        count++;

        cv::waitKey(1);  // Wait for a short delay
    }

    return 0;
}
