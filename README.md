# EyeLights Driver Monitoring system (DMS)

EyeLights DMS - designed to work with Nvidia Jetson and Qualcomm hardware.
Welcome to the Eyelights DMS (Driver Monitoring System) project! This system is designed to enhance driver safety and attentiveness by leveraging advanced technologies such as computer vision, artificial intelligence, and machine learning. The DMS system is specifically developed for Eyelights, a leading company in the automotive industry.

# Project Overview
The main objective of this project is to develop a robust DMS system using C++ and integrating it with the Eyelights BB SDK (Software Development Kit). The system operates both online and offline, ensuring continuous functionality even when an internet connection is not available. By leveraging cutting-edge AI/ML techniques, the DMS system provides various features to enhance driver safety and attentiveness.

# Key Features
The Eyelights DMS system incorporates several key features to monitor and analyze driver behavior. These features include:

**Feedback to External System**: The DMS system provides callback functions in the DMS SDK for all events and detections, enabling seamless integration with external systems.

**Facial Recognition**: The system utilizes facial recognition algorithms to detect and locate specific facial landmarks such as eyes, ears, lips, etc.

**Person Recognition**: Using facial recognition techniques, the DMS system can recognize previously defined individuals, allowing for personalized experiences and identification.

**Road Attention**: The system tracks the driver's gaze direction, determining whether they are focused on the road or not. An event is triggered if the driver's attention deviates for more than 2 seconds.

**Phone Usage Detection**: The DMS system can detect when the driver holds a phone in their hand(s) for longer than 2 seconds, helping to discourage distracted driving behavior.

**Drowsiness Detection**: By leveraging pre-trained models, the system attempts to identify signs of driver drowsiness, providing timely alerts to prevent accidents.

**Disturbance Level Analysis**: Using pre-trained models, the DMS system assesses the disturbance level of the driver, helping to evaluate their overall attentiveness.

# Repository Structure
This GitHub repository contains the source code and related files for the Eyelights DMS system. Here's an overview of the repository structure:

**eye_position**: Contains files related to eye position detection.
**face_detection**: Includes files for face detection algorithms.
**face_recognition**: Contains files for facial recognition and landmark detection.
**.gitignore**: Specifies files and directories to be ignored by Git version control.
**CHANGELOG.md**: Tracks the changes and updates made to the project over time.
**CODEOWNERS**: Specifies the code owners and their responsibilities within the project.
**README.md**: The file you're currently reading, providing an overview of the project and repository.

# Getting Started
To get started with the Eyelights DMS system, follow these steps:

Clone the repository to your local development environment:


`git clone https://github.com/YannickDurindelPro/Eyelights-DMS.git`


Explore the different directories and files to familiarize yourself with the project structure and code.

Execute the relevant components of the DMS system based on your requirements and desired functionality.

# Contributing
Contributions to the Eyelights DMS system are welcome! If you have any ideas, improvements, or bug fixes, please feel free to submit a pull request. Be sure to follow the existing coding style and adhere to the project's guidelines.

When contributing to this project, please keep in mind that the code and any contributions should align with Eyelights' goals and requirements for driver safety and attentiveness.
