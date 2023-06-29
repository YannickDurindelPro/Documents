#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <dirent.h>
#include <vector>
#include <string>

using namespace cv;
using namespace cv::face;

void trainAndSaveModel(const std::string& datasetPath, const std::string& savePath) {
    Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();

    // Load the training dataset
    std::vector<Mat> images;
    std::vector<int> labels;
    int currentLabel = 0;

    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(datasetPath.c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                const std::string classPath = datasetPath + entry->d_name;

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
    model->save(savePath);
}

int main() {
    std::string datasetPath = "/home/yannickdurindel/Documents/face_recognition/dataset/train-dataset/";
    std::string savePath = "model.xml";
    trainAndSaveModel(datasetPath, savePath);

    return 0;
}
