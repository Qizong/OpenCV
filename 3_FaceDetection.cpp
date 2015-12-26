/*
* To intercept X,Y of center of face object and sends them to Arduino Uno via serial
* Using two motors to move the Webcam to track face
*/
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <Windows.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay(Mat frame);


/** Global variables */
//-- Note, either copy these two files from opencv/data/haarscascades to your current folder, or change these locations
String face_cascade_name = "C:/OpenCV_2.4.9/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "C:/OpenCV_2.4.9/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection - Remixed by TechBitar";

// Serial to Arduino global declarations
int arduino_command;
Tserial *arduino_com;
short MSBLSB = 0;
unsigned char MSB = 0;
unsigned char LSB = 0;
// Serial to Arduino global declarations

int main(int argc, const char** argv)
{

	CvCapture* capture;
	Mat frame;

	// serial to Arduino setup 
	arduino_com = new Tserial();
	if (arduino_com != 0) 
	{
		arduino_com->connect("COM3", 57600, spNONE);
	}
	// serial to Arduino setup 

	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name))
	{ 
		printf("--(!)Error loading1\n");
		system("pause"); 
		return -1;
	};

	if (!eyes_cascade.load(eyes_cascade_name))
	{ 
		printf("--(!)Error loading2\n"); 
		system("pause"); 
		return -1;
	};

	//-- 2. Read the video stream
	capture = cvCaptureFromCAM(0);
	if (capture)
	{
		while (true)
		{
			frame = cvQueryFrame(capture);
			//-- 3. Apply the classifier to the frame
			if (!frame.empty())
			{
				detectAndDisplay(frame);
			}
			else
			{
				printf(" --(!) No captured frame -- Break!"); break;
			}

			int c = waitKey(10);
			if ((char)c == 27) { break; }
		}
	}
	// Serial to Arduino - shutdown
	arduino_com->disconnect();
	delete arduino_com;
	arduino_com = 0;
	// Serial to Arduino - shutdown
	system("pause");
	return 0;
}

/**
* @function detectAndDisplay
*/
void detectAndDisplay(Mat frame)
{

	vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(frame, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 2, 8, 0);
		cout << "X:" << faces[i].x  <<  "  y:" << faces[i].y  << endl;

		// send X,Y of face center to serial com port	
		// send X axis
		
		//cout << faces[i] << endl;

		// read least significant byte 
		LSB = faces[i].x & 0xff;
		// read next significant byte 
		MSB = (faces[i].x >> 8) & 0xff;

		
		arduino_com->sendChar(MSB);
		arduino_com->sendChar(LSB);

		// Send Y axis
		LSB = faces[i].y & 0xff;
		MSB = (faces[i].y >> 8) & 0xff;
		
		arduino_com->sendChar(MSB);
		arduino_com->sendChar(LSB);
		
		// serial com port send	 

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;
	}
	
	//-- Show what you got
	imshow(window_name, frame);

}
