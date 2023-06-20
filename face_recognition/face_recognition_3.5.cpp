#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>

int main() {
    // Load the face recognition model
    cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
    model->read("/home/yannickdurindel/Documents/face_recognition/model.xml");

    // Load the face detection model
    cv::CascadeClassifier faceCascade;
    faceCascade.load("/home/yannickdurindel/Documents/other/opencv/data/lbpcascades/lbpcascade_frontalface_improved.xml");

    // Initialize the camera
    cv::VideoCapture camera(0);  // Change the argument to the appropriate camera index if needed
    if (!camera.isOpened()) {
        std::cerr << "Failed to open the camera." << std::endl;
        return 1;
    }

    // Define the labels and corresponding person names
    std::vector<int> labels = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<std::string> personNames = {
        "Ilia_Seliverstov","Frederic_Aubert","Jean-Pierre_Stang","Jules_Gregoire"
        ,"Maelle_Neumann","Pascal_Chevallier","Romain_Duflot","Elsa_Ramond"
        ,"Quentin_Ailloud","Yannick_Durindel","Neyl_Boukerche","Stephane_Grange","Yoan_Dumas"
        ,"Aretem_Minenko","Evgeunii_Dombrovskii","Alexandre_Goudeau","Gaetan_Pons"
    };

    while (true) {
        // Capture a frame from the camera
        cv::Mat frame;
        camera.read(frame);

        // Convert the frame to grayscale
        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

        // Detect faces in the frame
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(grayFrame, faces);

        // Perform face recognition on the detected faces
        for (const auto& face : faces) {
            // Resize the face region to match the model's input size
            cv::Mat faceROI = grayFrame(face);
            cv::Mat resizedFace;
            cv::resize(faceROI, resizedFace, cv::Size(100, 100));

            // Predict the label of the face
            int predictedLabel = -1;
            double confidence = 0.0;
            model->predict(resizedFace, predictedLabel, confidence);
            std::cout << "Predicted Label: " << predictedLabel << std::endl;

            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);

            // Check if the predicted label is within the known labels range
            if (predictedLabel >= 0 && predictedLabel < labels.size()) {
                std::string personName = personNames[predictedLabel];

                // Draw bounding box and label on the frame
                cv::putText(frame, personName, cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
            }
            
            else {
                cv::putText(frame, "Unknown", cv::Point(face.x, face.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, cv::Scalar(0, 255, 0), 2);
            }
        }

        cv::imshow("Face Recognition", frame);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    camera.release();

    return 0;
}
