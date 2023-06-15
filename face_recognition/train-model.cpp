#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <string>

int main() {
    // Define the path to the directory containing the dataset images
    std::string datasetPath = "/home/yannickdurindel/Documents/face_recognition/dataset/train-dataset/me/";

    // Array of image names
    std::string imageNames[] = {
    "yannick_1.jpg", "yannick_2.jpg", "yannick_3.jpg", "yannick_4.jpg", "yannick_5.jpg", "yannick_6.jpg", 
    "yannick_7.jpg", "yannick_8.jpg", "yannick_9.jpg", "yannick_10.jpg", "yannick_11.jpg", "yannick_12.jpg", 
    "yannick_13.jpg", "yannick_14.jpg", "yannick_16.jpg", "yannick_17.jpg", "yannick_18.jpg", "yannick_19.jpg", 
    "yannick_20.jpg", "yannick_21.jpg", "yannick_22.jpg", "yannick_23.jpg", "yannick_24.jpg", "yannick_25.jpg", 
    "yannick_26.jpg", "yannick_27.jpg", "yannick_28.jpg", "yannick_29.jpg", "yannick_30.jpg", "yannick_31.jpg", 
    "yannick_32.jpg", "yannick_34.jpg", "yannick_35.jpg", "yannick_36.jpg", "yannick_37.jpg", "yannick_38.jpg", 
    "yannick_39.jpg", "yannick_40.jpg", "yannick_41.jpg", "yannick_42.jpg", "yannick_43.jpg", "yannick_44.jpg", 
    "yannick_45.jpg", "yannick_46.jpg", "yannick_47.jpg", "yannick_48.jpg", "yannick_49.jpg", "yannick_50.jpg", 
    "yannick_51.jpg", "yannick_52.jpg", "yannick_53.jpg", "yannick_54.jpg", "yannick_55.jpg", "yannick_56.jpg", 
    "yannick_57.jpg", "yannick_58.jpg", "yannick_59.jpg", "yannick_60.jpg", "yannick_61.jpg", "yannick_62.jpg", 
    "yannick_63.jpg", "yannick_64.jpg", "yannick_65.jpg", "yannick_66.jpg", "yannick_67.jpg", "yannick_68.jpg", 
    "yannick_69.jpg", "yannick_70.jpg", "yannick_71.jpg", "yannick_72.jpg", "yannick_73.jpg", "yannick_74.jpg", 
    "yannick_75.jpg", "yannick_76.jpg", "yannick_77.jpg", "yannick_78.jpg", "yannick_79.jpg", "yannick_80.jpg", 
    "yannick_81.jpg", "yannick_82.jpg", "yannick_83.jpg", "yannick_84.jpg", "yannick_85.jpg", "yannick_86.jpg", 
    "yannick_87.jpg", "yannick_88.jpg", "yannick_89.jpg", "yannick_90.jpg", "yannick_91.jpg", "yannick_92.jpg", 
    "yannick_93.jpg", "yannick_94.jpg", "yannick_95.jpg", "yannick_96.jpg", "yannick_97.jpg", "yannick_98.jpg", 
    "yannick_99.jpg", "yannick_100.jpg", "yannick_101.jpg", "yannick_102.jpg", "yannick_103.jpg", "yannick_104.jpg", 
    "yannick_105.jpg", "yannick_106.jpg", "yannick_107.jpg", "yannick_108.jpg", "yannick_109.jpg", "yannick_110.jpg", 
    "yannick_111.jpg", "yannick_112.jpg", "yannick_113.jpg", "yannick_114.jpg", "yannick_115.jpg", "yannick_116.jpg", 
    "yannick_117.jpg", "yannick_118.jpg", "yannick_119.jpg", "yannick_120.jpg", "yannick_121.jpg", "yannick_122.jpg", 
    "yannick_123.jpg", "yannick_124.jpg", "yannick_125.jpg", "yannick_126.jpg", "yannick_127.jpg", "yannick_128.jpg", 
    "yannick_129.jpg", "yannick_130.jpg", "yannick_131.jpg", "yannick_132.jpg", "yannick_133.jpg", "yannick_134.jpg", 
    "yannick_135.jpg", "yannick_136.jpg", "yannick_137.jpg", "yannick_138.jpg", "yannick_139.jpg", "yannick_140.jpg", 
    "yannick_141.jpg", "yannick_142.jpg", "yannick_143.jpg", "yannick_144.jpg", "yannick_145.jpg", "yannick_146.jpg", 
    "yannick_147.jpg", "yannick_148.jpg", "yannick_149.jpg", "yannick_150.jpg", "yannick_151.jpg", "yannick_152.jpg", 
    "yannick_153.jpg", "yannick_154.jpg", "yannick_155.jpg", "yannick_156.jpg", "yannick_157.jpg", "yannick_158.jpg", 
    "yannick_159.jpg", "yannick_160.jpg", "yannick_161.jpg", "yannick_162.jpg", "yannick_163.jpg", "yannick_164.jpg", 
    "yannick_165.jpg", "yannick_166.jpg", "yannick_167.jpg", "yannick_168.jpg", "yannick_169.jpg", "yannick_170.jpg", 
    "yannick_171.jpg", "yannick_172.jpg", "yannick_173.jpg", "yannick_174.jpg", "yannick_175.jpg", "yannick_176.jpg", 
    "yannick_177.jpg", "yannick_178.jpg", "yannick_179.jpg", "yannick_180.jpg", "yannick_181.jpg", "yannick_182.jpg", 
    "yannick_183.jpg", "yannick_184.jpg", "yannick_185.jpg", "yannick_186.jpg", "yannick_187.jpg", "yannick_188.jpg", 
    "yannick_189.jpg", "yannick_190.jpg", "yannick_191.jpg", "yannick_192.jpg", "yannick_193.jpg", "yannick_194.jpg", 
    "yannick_195.jpg", "yannick_196.jpg", "yannick_197.jpg", "yannick_198.jpg", "yannick_199.jpg", "yannick_200.jpg", 
    "yannick_201.jpg", "yannick_202.jpg", "yannick_203.jpg", "yannick_204.jpg", "yannick_205.jpg", "yannick_206.jpg", 
    "yannick_207.jpg", "yannick_208.jpg", "yannick_209.jpg", "yannick_210.jpg", "yannick_211.jpg", "yannick_212.jpg", 
    "yannick_213.jpg", "yannick_214.jpg", "yannick_215.jpg", "yannick_216.jpg", "yannick_217.jpg", "yannick_218.jpg", 
    "yannick_219.jpg", "yannick_220.jpg", "yannick_221.jpg", "yannick_222.jpg", "yannick_223.jpg", "yannick_224.jpg", 
    "yannick_225.jpg", "yannick_226.jpg", "yannick_227.jpg", "yannick_228.jpg", "yannick_229.jpg", "yannick_230.jpg", 
    "yannick_231.jpg", "yannick_232.jpg", "yannick_233.jpg", "yannick_234.jpg", "yannick_235.jpg", "yannick_236.jpg", 
    "yannick_237.jpg", "yannick_238.jpg", "yannick_239.jpg", "yannick_240.jpg", "yannick_241.jpg", "yannick_242.jpg", 
    "yannick_243.jpg", "yannick_244.jpg", "yannick_245.jpg", "yannick_246.jpg", "yannick_247.jpg", "yannick_248.jpg", 
    "yannick_249.jpg", "yannick_250.jpg", "yannick_251.jpg", "yannick_252.jpg", "yannick_253.jpg", "yannick_254.jpg", 
    "yannick_255.jpg", "yannick_256.jpg", "yannick_257.jpg", "yannick_258.jpg", "yannick_259.jpg", "yannick_260.jpg", 
    "yannick_261.jpg", "yannick_262.jpg", "yannick_263.jpg", "yannick_264.jpg", "yannick_265.jpg", "yannick_266.jpg", 
    "yannick_267.jpg", "yannick_268.jpg", "yannick_269.jpg", "yannick_270.jpg", "yannick_271.jpg", "yannick_272.jpg", 
    "yannick_273.jpg", "yannick_274.jpg", "yannick_275.jpg", "yannick_276.jpg", "yannick_277.jpg", "yannick_278.jpg", 
    "yannick_279.jpg", "yannick_280.jpg", "yannick_281.jpg", "yannick_282.jpg", "yannick_283.jpg", "yannick_284.jpg", 
    "yannick_285.jpg", "yannick_286.jpg", "yannick_287.jpg", "yannick_288.jpg", "yannick_289.jpg", "yannick_290.jpg", 
    "yannick_291.jpg", "yannick_292.jpg", "yannick_293.jpg", "yannick_294.jpg", "yannick_295.jpg", "yannick_296.jpg", 
    "yannick_297.jpg", "yannick_298.jpg", "yannick_299.jpg", "yannick_300.jpg", "yannick_301.jpg", "yannick_302.jpg", 
    "yannick_303.jpg", "yannick_304.jpg", "yannick_305.jpg", "yannick_306.jpg", "yannick_307.jpg", "yannick_308.jpg", 
    "yannick_309.jpg", "yannick_310.jpg", "yannick_311.jpg", "yannick_312.jpg", "yannick_313.jpg", "yannick_314.jpg", 
    "yannick_315.jpg", "yannick_316.jpg", "yannick_317.jpg", "yannick_318.jpg", "yannick_319.jpg", "yannick_320.jpg", 
    "yannick_321.jpg", "yannick_322.jpg", "yannick_323.jpg", "yannick_324.jpg", "yannick_325.jpg", "yannick_326.jpg", 
    "yannick_327.jpg", "yannick_328.jpg", "yannick_329.jpg", "yannick_330.jpg", "yannick_331.jpg", "yannick_332.jpg", 
    "yannick_333.jpg", "yannick_334.jpg", "yannick_335.jpg", "yannick_336.jpg", "yannick_337.jpg", "yannick_338.jpg", 
    "yannick_339.jpg", "yannick_340.jpg", "yannick_341.jpg", "yannick_342.jpg", "yannick_343.jpg", "yannick_344.jpg", 
    "yannick_345.jpg", "yannick_346.jpg", "yannick_347.jpg", "yannick_348.jpg", "yannick_349.jpg", "yannick_350.jpg", 
    "yannick_351.jpg", "yannick_352.jpg", "yannick_353.jpg", "yannick_354.jpg", "yannick_355.jpg", "yannick_356.jpg", 
    "yannick_357.jpg", "yannick_358.jpg", "yannick_359.jpg", "yannick_360.jpg", "yannick_361.jpg", "yannick_362.jpg", 
    "yannick_363.jpg", "yannick_364.jpg", "yannick_365.jpg", "yannick_366.jpg", "yannick_367.jpg", "yannick_368.jpg", 
    "yannick_369.jpg", "yannick_370.jpg", "yannick_371.jpg", "yannick_372.jpg", "yannick_373.jpg", "yannick_374.jpg", 
    "yannick_375.jpg", "yannick_376.jpg", "yannick_377.jpg", "yannick_378.jpg", "yannick_379.jpg", "yannick_380.jpg", 
    "yannick_381.jpg", "yannick_382.jpg", "yannick_383.jpg", "yannick_384.jpg", "yannick_385.jpg", "yannick_386.jpg", 
    "yannick_387.jpg", "yannick_388.jpg", "yannick_389.jpg", "yannick_390.jpg", "yannick_391.jpg", "yannick_392.jpg", 
    "yannick_393.jpg", "yannick_394.jpg", "yannick_395.jpg", "yannick_396.jpg", "yannick_397.jpg", "yannick_398.jpg", 
    "yannick_399.jpg"
    };

    // Read the dataset and labels
    std::vector<cv::Mat> images;
    std::vector<int> labels;

    // Loop through the image names array
    for (const std::string& imageName : imageNames) {
        std::string imagePath = datasetPath + imageName;
        cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

        // Resize the image to a consistent size (e.g., 100x100)
        //cv::resize(image, image, cv::Size(115, 115));

        // Add the image and corresponding label to the vectors
        images.push_back(image);
        labels.push_back(images.size() - 1);
    }


    // Create and train the LBPHFaceRecognizer model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->train(images, labels);

    // Save the trained model
    model->save("models/model_me.xml");

    return 0;
}
