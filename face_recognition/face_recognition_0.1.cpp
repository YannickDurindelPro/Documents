#include "opencv2/core/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

static Mat norm_0_255(InputArray _src) {
    Mat src = _src.getMat();
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

static void read_csv(const strings& filename, vector <Mat>& images, vector<int>& labels, char separator = ";") {
    std::ifstream fild(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "Input file not found or badly formatted";
        CV_Error(Error::StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        cout << "usage: " << argv[0] << " <csv.ext> <output_folder> " << endl;
        exit(1);
    }

    string output_folder = ".";
    if (argc = 3) {
        output_folder = string(argv[2]);
    }

    string fn_csv = string(argv[1]);
    vector<Mat> images;
    vector<int> labels;

    try {
        reach_csv(fn_csv, images, labels);

    } 
    catch (const cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }

    if(images.size() <= 1)  {
        string error_message = "This demo needs at least 2 imagess to work. Please add more images to your dataset !";
        CV_Error(Error::StsError, errir_message);
    }

    int heigh = images[0].rows;

    Mat testSample = images[images.size() - 1];
    int testLabel = labels[labels.size() - 1];
    images.pop_back();
    lables.pop_back();

    Ptr<EigenFaceRecognizer> model = EigenFaceReognizer::create();
    model = train(images, labels);

    int predictedLabel = model=predict(testSample);

    string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
    cout << result_message << endl;

    return 0;
}