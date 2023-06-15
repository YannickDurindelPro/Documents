#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>

int main() {
    // Define the path to the directory containing the dataset images
    std::string datasetPath = "/home/yannickdurindel/Documents/face_recognition/dataset/train-dataset/s0/";

    // Array of image names
    std::string imageNames[] = {
        "0000_02176.pgm", "0000_02421.pgm", "0000_02561.pgm", "0000_02774.pgm", "0000_03524.pgm",
        "0000_02179.pgm", "0000_02422.pgm", "0000_02569.pgm", "0000_02775.pgm", "0000_03528.pgm",
        "0000_02194.pgm", "0000_02428.pgm", "0000_02575.pgm", "0000_02812.pgm", "0000_03529.pgm",
        "0000_02199.pgm", "0000_02429.pgm", "0000_02576.pgm", "0000_02814.pgm", "0000_03530.pgm",
        "0000_02201.pgm", "0000_02430.pgm", "0000_02577.pgm", "0000_02827.pgm", "0000_03531.pgm",
        "0000_02212.pgm", "0000_02432.pgm", "0000_02578.pgm", "0000_02830.pgm", "0000_03532.pgm",
        "0000_02223.pgm", "0000_02435.pgm", "0000_02583.pgm", "0000_02843.pgm", "0000_03534.pgm",
        "0000_02225.pgm", "0000_02436.pgm", "0000_02590.pgm", "0000_02844.pgm", "0000_03535.pgm",
        "0000_02240.pgm", "0000_02438.pgm", "0000_02591.pgm", "0000_02845.pgm", "0000_03536.pgm",
        "0000_02244.pgm", "0000_02439.pgm", "0000_02592.pgm", "0000_02854.pgm", "0000_03551.pgm",
        "0000_02246.pgm", "0000_02440.pgm", "0000_02593.pgm", "0000_02939.pgm", "0000_03592.pgm",
        "0000_02255.pgm", "0000_02442.pgm", "0000_02594.pgm", "0000_02940.pgm", "0000_03720.pgm",
        "0000_02261.pgm", "0000_02443.pgm", "0000_02596.pgm", "0000_02941.pgm", "0000_03723.pgm",
        "0000_02274.pgm", "0000_02446.pgm", "0000_02597.pgm", "0000_02967.pgm", "0000_03733.pgm",
        "0000_02281.pgm", "0000_02448.pgm", "0000_02598.pgm", "0000_02968.pgm", "0000_03757.pgm",
        "0000_02283.pgm", "0000_02449.pgm", "0000_02599.pgm", "0000_02969.pgm", "0000_03759.pgm",
        "0000_02286.pgm", "0000_02459.pgm", "0000_02600.pgm", "0000_02970.pgm", "0000_03762.pgm",
        "0000_02287.pgm", "0000_02460.pgm", "0000_02601.pgm", "0000_02971.pgm", "0000_03772.pgm",
        "0000_02290.pgm", "0000_02461.pgm", "0000_02603.pgm", "0000_02974.pgm", "0000_03773.pgm",
        "0000_02291.pgm", "0000_02464.pgm", "0000_02611.pgm", "0000_02975.pgm", "0000_03779.pgm",
        "0000_02294.pgm", "0000_02466.pgm", "0000_02613.pgm", "0000_02976.pgm", "0000_03781.pgm",
        "0000_02295.pgm", "0000_02467.pgm", "0000_02614.pgm", "0000_02982.pgm", "0000_03859.pgm",
        "0000_02298.pgm", "0000_02468.pgm", "0000_02615.pgm", "0000_02985.pgm", "0000_04637.pgm",
        "0000_02299.pgm", "0000_02471.pgm", "0000_02617.pgm", "0000_02997.pgm", "0000_04786.pgm",
        "0000_02303.pgm", "0000_02472.pgm", "0000_02619.pgm", "0000_02999.pgm", "0000_04787.pgm",
        "0000_02304.pgm", "0000_02475.pgm", "0000_02623.pgm", "0000_03311.pgm", "0000_04788.pgm",
        "0000_02316.pgm", "0000_02477.pgm", "0000_02624.pgm", "0000_03319.pgm", "0000_04789.pgm",
        "0000_02317.pgm", "0000_02478.pgm", "0000_02628.pgm", "0000_03328.pgm", "0000_04790.pgm",
        "0000_02323.pgm", "0000_02480.pgm", "0000_02632.pgm", "0000_03347.pgm", "0000_04791.pgm",
        "0000_02331.pgm", "0000_02481.pgm", "0000_02711.pgm", "0000_03375.pgm", "0000_05147.pgm",
        "0000_02335.pgm", "0000_02485.pgm", "0000_02712.pgm", "0000_03402.pgm", "0000_05148.pgm",
        "0000_02350.pgm", "0000_02488.pgm", "0000_02713.pgm", "0000_03501.pgm", "0000_05149.pgm",
        "0000_02359.pgm", "0000_02493.pgm", "0000_02716.pgm", "0000_03503.pgm", "0000_05194.pgm",
        "0000_02365.pgm", "0000_02495.pgm", "0000_02717.pgm", "0000_03507.pgm", "0000_05195.pgm",
        "0000_02402.pgm", "0000_02499.pgm", "0000_02718.pgm", "0000_03508.pgm", "0000_05196.pgm",
        "0000_02403.pgm", "0000_02502.pgm", "0000_02731.pgm", "0000_03516.pgm", "0000_05198.pgm",
        "0000_02414.pgm", "0000_02513.pgm", "0000_02732.pgm", "0000_03517.pgm", "0000_05223.pgm",
        "0000_02416.pgm", "0000_02528.pgm", "0000_02733.pgm", "0000_03518.pgm", "0000_05235.pgm",
        "0000_02417.pgm", "0000_02557.pgm", "0000_02768.pgm", "0000_03522.pgm", "0000_05242.pgm",
        "0000_02420.pgm", "0000_02558.pgm", "0000_02773.pgm", "0000_03523.pgm", "0000_05243.pgm"
    };

    // Read the dataset and labels
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    // Loop through the image names array
    for (const std::string& imageName : imageNames) {
        std::string imagePath = datasetPath + imageName;
        cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

        // Resize the image to a consistent size (e.g., 100x100)
        cv::resize(image, image, cv::Size(100, 100));

        // Add the image and corresponding label to the vectors
        images.push_back(image);
        labels.push_back(images.size() - 1);
    }


    // Create and train the LBPHFaceRecognizer model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->train(images, labels);

    // Save the trained model
    model->save("model.xml");

    return 0;
}
