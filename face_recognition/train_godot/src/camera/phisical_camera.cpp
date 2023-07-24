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

        // Define the labels and corresponding person names
        std::vector<int> labels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        std::vector<std::string> personNames = {
            "Frederic_Aubert", "Jean-Pierre_Stang", "Jules_Gregoire", "Neyl_Boukerche", "Pascal_Chevallier", "Alexandre_Goudeau", "Jerome_Pauc",
            "Evgeunii_Dombrovskii", "Ilia_Seliverstov", "Stephane_Grange", "Yannick_Durindel", "Nicolas_Hourcastagnou"
        };

        // Vector to store image paths
        std::vector<std::string> imagePaths;

        // Read the dataset and labels
        std::vector<cv::Mat> images;
        std::vector<int> index;

        // Initialize the label counter
        int labelCounter = 0;

        // Iterate over folders in the dataset root directory
        for (int i = 0 ; i < 16 ; i++) {

            std::string personName = personNames[i];
            std::cout << "Training for person: " << personName << std::endl;

            // Loop through the image paths
            for (int j = 0 ; j < 500 ; j++) {
                std::string imagePath = std::string(datasetRootPath) + std::string(personName) + "/" + std::string(personName) + std::to_string(i) + ".jpg";
                cv::Mat image = cv::imread(imagePath);

                if (image.empty()) {
                    std::cerr << "Failed to read image: " << imagePath << std::endl;
                    continue;
                }

                cv::Mat adjustedImage;
                image.convertTo(adjustedImage, -1, 1, 0);  // Increase brightness by a factor of 1.5

                // Resize the image to a consistent size (e.g., 100x100)
                cv::resize(image, image, cv::Size(500, 500));

                // Add the image and corresponding label to the vectors
                images.push_back(image);
                index.push_back(labelCounter);  // Assign incremental labels for training

                //std::cout << "Added image: " << imagePath << "labelCounter : " << labelCounter << std::endl;
            }

            // Increment the label counter for the next person
            labelCounter++;

            // Clear imagePaths for the next person
            imagePaths.clear();
        }

        // Create and train the LBPHFaceRecognizer model
        cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create(1,8,8,8,80);
        model->train(images, labels);

        // Save the trained model
        std::string modelPath = "/home/eyelights/Documents/face_recognition/model.xml";
        model->save(modelPath);

        return 0;
    }

    void PhisicalCamera::shutdown() {
        cv::destroyWindow("Camera");
    }

}}