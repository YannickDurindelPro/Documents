#include "phisical_camera.hpp"

namespace EyeLights { namespace EyeRecognizer {
    using namespace godot;
    using namespace std;
    using namespace cv;

    PhisicalCamera::PhisicalCamera() {
        image.instantiate();
        texture.instantiate();
    }

    PhisicalCamera::~PhisicalCamera() {

    }

    void PhisicalCamera::_bind_methods() {
        std::cout << "PhisicalCamera::_bind_methods()" << std::endl;
        ClassDB::bind_method(D_METHOD("open"), &PhisicalCamera::open);
    }

    bool PhisicalCamera::open(int cameraId) {
        // Define the path to the directory containing the dataset images
        std::string datasetRootPath = "/home/eyelights/Documents/face_recognition/dataset/train-dataset/";

        // Vector to store image paths
        std::vector<std::string> imagePaths;

        // Read the dataset and labels
        std::vector<cv::Mat> images;
        std::vector<int> labels;

        // Initialize the label counter
        int labelCounter = 0;

        // Iterate over folders in the dataset root directory
        for (const auto& personDir : std::experimental::filesystem::directory_iterator(datasetRootPath)) {
            if (!personDir.is_directory()) {
                continue;
            }

            std::string personName = personDir.path().filename().string();
            std::cout << "Training for person: " << personName << std::endl;

            // Iterate over files in the person's directory
            for (const auto& entry : std::experimental::filesystem::directory_iterator(personDir.path())) {
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

                cv::Mat adjustedImage;
                image.convertTo(adjustedImage, -1, 1, 0);  // Increase brightness by a factor of 1.5


                // Resize the image to a consistent size (e.g., 100x100)
                cv::resize(image, image, cv::Size(500,500));

                // Add the image and corresponding label to the vectors
                images.push_back(image);
                labels.push_back(labelCounter);  // Assign incremental labels for training

                //std::cout << "Added image: " << imagePath << "labelCounter : " << labelCounter << std::endl;
            }

            // Increment the label counter for the next person
            labelCounter++;

            // Clear imagePaths for the next person
            imagePaths.clear();
        }

        // Create and train the LBPHFaceRecognizer model
        cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create(1, 8, 8, 8, 80.0);       //(Radius, Neighbour : Precision, Grid, Threshold : Confidence)
        model->train(images, labels);

        // Save the trained model
        std::string modelPath = "model.xml";
        model->save(modelPath);

        return 0;
    }


    void PhisicalCamera::_process(double delta) {
        if (isOpened) {
            cap >> currentFrame;
            if (!currentFrame.empty()) {
                cv::imshow("Camera", currentFrame);
                cv::waitKey(1);
            }
        }
    }

    void PhisicalCamera::shutdown() {
        cv::destroyWindow("Camera");
    }

}}