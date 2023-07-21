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
        ClassDB::bind_method(D_METHOD("show"), &PhisicalCamera::_process);
    }

    bool PhisicalCamera::open() {
        // VideoCapture class for playing video for which faces to be detected
        cv::VideoCapture capture;
        cv::Mat frame, image;
    
        // PreDefined trained XML classifiers with facial features
        CascadeClassifier cascade, nestedCascade;
        double scale=1;
    
        // Load classifiers from "opencv/data/haarcascades" directory
        nestedCascade.load( "/usr/share/opencv4/haarcascades/haarcascade_eye_tree_eyeglasses.xml" ) ;
    
        // Change path before execution
        cascade.load( "/usr/share/opencv4/haarcascades/haarcascade_frontalcatface.xml" ) ;
    
        // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
        capture.open("http://192.168.1.188:4747/video");
        if( capture.isOpened() )
        {
            // Capture frames from video and detect faces
            cout << "Face Detection Started...." << endl;
            while(1)
            {
                capture >> frame;
                if( frame.empty() )
                    std::cerr << "frame is empty" << std::endl;
                    break;
                Mat frame1 = frame.clone();

                vector<Rect> faces, faces2;
                Mat gray, smallImg;
            
                cvtColor( image, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale
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
                    Mat smallImgROI;
                    vector<Rect> nestedObjects;
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

                    if( nestedCascade.empty() )
                        continue;
                    smallImgROI = smallImg( r );
                    
                    // Detection of eyes in the input image
                    nestedCascade.detectMultiScale( smallImgROI, nestedObjects, 1.05, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
                    
                    // Draw rectangles around eyes
                    for (size_t j = 0; j < nestedObjects.size(); j++)
                    {
                        Rect nr = nestedObjects[j];
                        Rect eyeRect(cvRound((r.x + nr.x) * scale), cvRound((r.y + nr.y) * scale),cvRound(nr.width * scale), cvRound(nr.height * scale));
                        rectangle(image, eyeRect, color, 3, 8, 0);
                    }
                }
            
                // Show Processed Image with detected faces
                imshow( "Face Detection", image );
                
                char c = (char)waitKey(10);
            
                // Press q to exit from window
                if( c == 27 || c == 'q' || c == 'Q' )
                    break;
            }
        }
        else
            cout<<"Could not Open Camera";
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
