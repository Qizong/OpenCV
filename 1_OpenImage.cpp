//**********************************************************
// *** Load picture from file and create a gray picture. ***
//**********************************************************
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	//read the image data in the file "MyPic.JPG" and store it in 'img'
	Mat img = imread("C:\\Users\\QizongWu\\Documents\\C++\\OpenImageCV\\pic.JPG", CV_LOAD_IMAGE_UNCHANGED); 
	//create an image ( 3 channels, 8 bit image depth, 500 high, 1000 wide, (100, 100, 100) - RGB)
	Mat img1(500, 1000, CV_8UC3, Scalar(100, 100, 100)); 

	//check whether the image is loaded or not
	if (img.empty()) 
	{
		cout << "Error: Image cannot be loaded!" << endl;
		system("pause"); //wait for a key press
		return -1;
	}
	// If the Image cannot be created, display warning.
	if (img1.empty()) 
	{
		cout << "Error: the Image cannot be created!" << endl;
		system("pause"); //wait for a key press
		return -1;
	}

	//create a window named "MyImage"
	namedWindow("MyImage", CV_WINDOW_AUTOSIZE); 
	//display image
	imshow("MyImage", img); 
	cout << "First image loaded successfully!" << endl;

	//create a blank window with color
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow("MyWindow", img1); //display the image which is stored in the 'img' in the "MyWindow" window
	
	waitKey(0);
		
	// kill the window
	destroyWindow("MyImage"); 
	destroyWindow("MyWindow");

	return 0;
}