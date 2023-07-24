#include "phisical_camera.hpp"

namespace EyeLights { namespace EyeRecognizer {
    using namespace godot;
    using namespace std;
    using namespace cv;

    PhisicalCamera::PhisicalCamera() {
        image.instantiate();
        texture.instantiate();
    }

    PhisicalCamera::~PhisicalCamera() {

    }

    void PhisicalCamera::_bind_methods() {
        std::cout << "PhisicalCamera::_bind_methods()" << std::endl;
        ClassDB::bind_method(D_METHOD("open"), &PhisicalCamera::open);
    }

    bool PhisicalCamera::open(int cameraId) {

        // VideoCapture class for playing video for which faces to be detected
        VideoCapture capture;
        Mat frame;
    
        // PreDefined trained XML classifiers with facial features
        CascadeClassifier cascade;
        double scale=1;
    
        // Load classifiers from "opencv/data/haarcascades" directory
        cascade.load( "/usr/share/opencv4/lbpcascades/lbpcascade_frontalface_improved.xml" ) ;
    
        // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
        cv::VideoCapture cap(cameraId); // Open the default camera (usually the first camera available)

        if (!cap.isOpened()) {
            std::cout << "Error: Could not open the camera.\n";
            return 0;
        }

        cv::namedWindow("Camera Feed", cv::WINDOW_NORMAL); // Create a window to display the camera feed
        // Capture frames from video and detect faces
        cout << "Face Detection Started...." << endl;

        while (true) {
            cv::Mat frame;
            cap >> frame; // Capture a frame from the camera

            if (frame.empty()) {
                std::cout << "Error: Failed to capture frame.\n";
                break;
            }
            Mat image = frame.clone();

            //face detectio seccion
            vector<Rect> faces, faces2;
            Mat gray, smallImg;
        
            cvtColor( frame, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale
            double fx = 1 / scale;

            // Resize the Grayscale Image
            resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
            equalizeHist( smallImg, smallImg );
            double brightness = 150; // Adjust this value as needed
            cv::Mat brightImg = smallImg + cv::Scalar(brightness, brightness, brightness);

            // Detect faces of different sizes using cascade classifier
            cascade.detectMultiScale(brightImg, faces, 1.2, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

            // Draw circles around the faces
            for ( size_t i = 0; i < faces.size(); i++ )
            {
                Rect r = faces[i];
                Point center;
                Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
                int radius;
        
                double aspect_ratio = (double)r.width/r.height;
                if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
                {
                    Rect faceRect(cvRound(r.x * scale), cvRound(r.y * scale),cvRound(r.width * scale), cvRound(r.height * scale));
                    rectangle(image, faceRect, (0,0,0), 3, 8, 0);
                }
                else
                rectangle(image, cv::Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                    cv::Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                    cv::Scalar(255, 0, 0), 3, 8, 0);
            }

            //end of face detection code*

            cv::imshow("Camera Feed", image); // Display the frame in the window

            char key = cv::waitKey(1); // Wait for a key press (1ms delay)
            if (key == 27) { // If the 'Esc' key is pressed, break the loop
                break;
            }
        }

        cap.release(); // Release the camera
        cv::destroyAllWindows(); // Close all OpenCV windows
        return 0;
    }


    void PhisicalCamera::_process(double delta) {
        if (isOpened) {
            cap >> currentFrame;
            if (!currentFrame.empty()) {
                cv::imshow("Camera", currentFrame);
                cv::waitKey(1);
            }
        }
    }

    void PhisicalCamera::shutdown() {
        cv::destroyWindow("Camera");
    }

}}