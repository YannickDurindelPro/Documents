#ifndef CAMERA_WRAPPER_HPP
#define CAMERA_WRAPPER_HPP

#include <opencv2/opencv.hpp>

class CameraWrapper {
public:
    CameraWrapper();
    ~CameraWrapper();

    bool openCamera(int cameraIndex);
    void closeCamera();
    bool isCameraOpened() const;

    cv::Mat getFrame();

private:
    cv::VideoCapture camera;
};

#endif // CAMERA_WRAPPER_HPP
