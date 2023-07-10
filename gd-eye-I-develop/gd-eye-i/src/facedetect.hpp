#ifndef CAMERA_OPENCV_HPP
#define CAMERA_OPENCV_HPP

#include <opencv2/opencv.hpp>
#include </usr/include/godot_cpp/godot.hpp>
#include <dict_handler.hpp>

class CameraOpenCV : public CameraFeed {
    GODOT_CLASS(CameraOpenCV, CameraFeed)

private:
    cv::VideoCapture capture;

public:
    static void _register_methods();

    void _init();  // Constructor
    void _process(float delta);  // Frame processing function
    void _capture_frame();  // Capture a frame from the camera
};

#endif // CAMERA_OPENCV_HPP
