#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0); // open webcam Logitech C310

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Error: capWebcam not accessed successfully!" << endl;
		system("pause");
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	// Display the Frame Size of the video
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	//create a window called "WebcamHD"
	namedWindow("WebcamHD", CV_WINDOW_AUTOSIZE); 

	while (1)
	{
		Mat frame;

		bool bSuccess_frame = cap.read(frame); // read a new frame from video

		if (!bSuccess_frame) //If cannot read fram info, break and display warning.
		{
			cout << "Cannot read a frame from Webcam" << endl;
			system("pause");
			break;
		}

		imshow("WebcamHD", frame); // Show the frame in "WebcamHD" window

		if (waitKey(30) == 27) // Wait for 'Esc' key press for 30ms. If 'Esc' is pressed, break loop.
		{
			cout << "esc key is pressed by user" << endl;
			break;
			system("pause");
		}
		
	}
	cout << "1st Webcam Capture succeeded!" << endl;
	system("pause");
	return 0;

}