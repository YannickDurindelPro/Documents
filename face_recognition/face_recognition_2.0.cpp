#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>
#include <vector>

cv::CascadeClassifier classifier;
cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();

int extractfaces(cv::Mat &img, cv::Mat &face) {
  cv::Mat img_gray;
  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
  std::vector<cv::Rect> features;
  classifier.detectMultiScale(img, features);

  /* Under Assumption that image consist of only single face */
  if (features.size() > 0) {
    face = img_gray(features[0]);
    return 1;
  } else
    return 0;
}

void train_dataset(const std::string &in_dir) {
  std::cout << "Starting To Train Dataset...\n";

  std::vector<int> faceIds;
  std::vector<cv::Mat> faceSamples;

  for (const auto &file : std::filesystem::directory_iterator(in_dir)) {
    std::string label = file.path().filename();
    std::cout << "Images in directory: " << label << "...\n";

    /*Directory Format: dir_name_0 ,dir_name_1 */
    int faceID = std::stoi(label.substr(label.rfind("_") + 1, label.size()));

    for (const auto &f : std::filesystem::directory_iterator(file.path())) {
      cv::Mat src, face;
      std::cout << f << "\n";
      src = cv::imread(f.path());
      if (extractfaces(src, face)) {
        faceSamples.emplace_back(face);
        faceIds.emplace_back(faceID);
      }
    }
    model->train(faceSamples, faceIds);
    std::cout << "Done!!\n";
  }

  std::cout << "Training Datasets Done !! \n";
}

void test_dataset(const std::string &in_dir) {
  std::cout << "Testing Datasets... \n";
  const std::vector<std::string> names = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}; // Arrange name according to
                                                // directory in train_dataset

  for (const auto &file : std::filesystem::directory_iterator(in_dir)) {
    cv::Mat src = cv::imread(file.path());
    cv::Mat face;
    extractfaces(src, face);
    int predictedLabel = -1;
    double confidence = 0.0;
    model->predict(face, predictedLabel, confidence);
    std::cout << predictedLabel << "\n";

    /* If No Match Found prediction will be -1 */
    if (predictedLabel != -1) {
      cv::putText(src, names[predictedLabel], cv::Point(10, src.rows / 2),
                  cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 185, 0), 1);

      cv::imshow(file.path().filename(), src);

      std::cout << "File: " << file.path().filename()
                << "\nPrediction: " << names[predictedLabel]
                << "\nConfidence: " << confidence << "\n\n\n";
    } else {
      cv::putText(src, "Match Not Found", cv::Point(10, src.rows / 2),
                  cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 185, 0), 1);

      cv::imshow(file.path().filename(), src);
      std::cout << "File: " << file.path().filename()
                << "Prediction: Unknown To Model"
                << "\n";
    }
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "!! ERROR !!!\n";
    std::cout << "<Program> <DatasetFolder> <Test Folder>\n";
    for (int i = 0; i < argc; ++i) {
      std::cout << argv[i] << std::endl;
    }
    return -1;
  }

  std::cout << "Loading Haarcascade File ...\n";
  assert(classifier.load("~/Documents/other/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"));
  std::cout << "Done!!\n";

  train_dataset(argv[1]);

  test_dataset(argv[2]);

  cv::waitKey(0);

  return 0;
}