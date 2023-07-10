#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <dirent.h>
#include <vector>
#include <string>
#include <godot-cpp/godot.hpp>
#include <Reference.hpp>

using namespace cv;
using namespace cv::face;
using namespace godot;

class FaceRecognition : public Reference {
    GODOT_CLASS(FaceRecognition, Reference)

public:
    static void _register_methods() {
        register_method("_train_and_save_model", &FaceRecognition::_train_and_save_model);
    }

    void _train_and_save_model(String datasetPath, String savePath) {
        Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();

        // Convert datasetPath and savePath from Godot String to std::string
        std::string datasetPathStr = datasetPath.utf8().get_data();
        std::string savePathStr = savePath.utf8().get_data();

        // Load the training dataset
        std::vector<Mat> images;
        std::vector<int> labels;
        int currentLabel = 0;

        DIR* dir;
        struct dirent* entry;
        if ((dir = opendir(datasetPathStr.c_str())) != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                    const std::string classPath = datasetPathStr + entry->d_name;

                    DIR* classDir;
                    struct dirent* imageEntry;
                    if ((classDir = opendir(classPath.c_str())) != NULL) {
                        while ((imageEntry = readdir(classDir)) != NULL) {
                            if (imageEntry->d_type == DT_REG) {
                                const std::string imagePath = classPath + "/" + imageEntry->d_name;
                                Mat image = imread(imagePath, IMREAD_GRAYSCALE);

                                labels.push_back(currentLabel);
                                images.push_back(image);
                            }
                        }
                        closedir(classDir);
                    }

                    currentLabel++;
                }
            }
            closedir(dir);
        }

        // Train the face recognition model
        model->train(images, labels);

        // Save the trained model
        model->save(savePathStr);
    }
};

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options* o) {
    Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options* o) {
    Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void* handle) {
    Godot::nativescript_init(handle);

    register_class<FaceRecognition>();
}
