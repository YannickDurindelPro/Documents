#include "facedetect.hpp"

using namespace godot;

void CameraOpenCV::_register_methods() {
    register_method("_process", &CameraOpenCV::_process);
    register_method("_capture_frame", &CameraOpenCV::_capture_frame);
}

void CameraOpenCV::_init() {
    // Set up the VideoCapture with the default camera
    capture.open(0);  // Use 0 for the default camera, or specify the camera index

    // Check if the camera opened successfully
    if (!capture.isOpened()) {
        Godot::print_error("Failed to open camera.", __FUNCTION__, __FILE__, __LINE__);
    }
}

void CameraOpenCV::_process(float delta) {
    // Process frames here
    _capture_frame();
    // ... Perform additional image processing using OpenCV ...
}

void CameraOpenCV::_capture_frame() {
    // Check if the camera is opened
    if (!capture.isOpened()) {
        return;
    }

    cv::Mat frame;
    capture.read(frame);

    // Convert the OpenCV frame to Godot Image
    int width = frame.cols;
    int height = frame.rows;
    Image image;
    image.create(width, height, false, Image::FORMAT_RGB8);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);
            Color color(pixel[2] / 255.0, pixel[1] / 255.0, pixel[0] / 255.0);
            image.set_pixel(x, y, color);
        }
    }

    // Emit the captured frame as a Godot signal
    emit_signal("frame_captured", image);
}
