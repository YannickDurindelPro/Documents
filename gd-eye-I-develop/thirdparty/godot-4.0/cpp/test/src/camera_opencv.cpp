#include "camera_opencv.hpp"

CameraWrapper::CameraWrapper() {
    // Constructor implementation
}

CameraWrapper::~CameraWrapper() {
    // Destructor implementation
    closeCamera();
}

bool CameraWrapper::openCamera(int cameraIndex) {
    closeCamera(); // Close any previously opened camera

    camera.open(cameraIndex);

    return isCameraOpened();
}

void CameraWrapper::closeCamera() {
    if (isCameraOpened()) {
        camera.release();
    }
}

bool CameraWrapper::isCameraOpened() const {
    return camera.isOpened();
}

cv::Mat CameraWrapper::getFrame() {
    cv::Mat frame;
    camera.read(frame);

    return frame;
}
