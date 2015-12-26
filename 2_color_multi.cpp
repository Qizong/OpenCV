// Region of Interest
#include <cv.h>  
#include <highgui.h>  
#include <iostream>  

// Namespace    
using namespace cv;
using namespace std;

// Functions 
bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

int main()
{
	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
	{
		cout << "Image successfully edited! :D" << endl;
	}
	else
	{
		cout << "Image cannot be edited!! :(" << endl;
	}
	waitKey(0);
	system("pause");
	return 0;
}

bool ROI_AddImage()
{

	// Load Image from File  
	Mat Image_org1 = imread("eva_origin.jpg");
	Mat Image_logo = imread("eva_logo.jpg");

	if (!Image_org1.data) 
	{ 
		printf("Wrong! Cannot load image 1 \n"); 
		return 0; 
	}

	if (!Image_logo.data) 
	{ 
		printf("Wrong! Cannot load logo 1"); 
		return 0; 
	}

	// Select the Region of Iterest
	Mat imageROI = Image_org1(Rect(0, 0, Image_logo.cols, Image_logo.rows));

	// Add a mask to make logo gray 
	Mat mask = imread("eva_logo.jpg", 0);

	// Copy mask to ROI  
	Image_logo.copyTo(imageROI, mask);

	// Display image adding logo
	namedWindow("Multi Images in a Window");
	imshow("Multi Images in a Window", Image_org1);

	
	return 1;

	system("pause");
}

//---------------------------------LinearBlending-------------------------------------  
// Name: LinearBlending
// Using addWeighted Function to linearly blend two images
// Date: 11/18/2015
//--------------------------------------------------------------------------------------------  
bool LinearBlending()
{
	//【0】定义一些局部变量  
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// Load Image
	srcImage2 = imread("mushroom.jpg");
	srcImage3 = imread("rain.jpg");

	if (!srcImage2.data) 
	{ 
		printf("Cannot load image! Error Window 2 \n");
		return 0; 
	}
	if (!srcImage3.data) 
	{ 
		printf("Cannot load image! Error Window 2 \n");
		return 0; 
	}

	// Weight Image 
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// Display Images
	namedWindow("2. Linear Blending - Original", 1);
	imshow("2. Linear Blending - Original", srcImage2);

	namedWindow("3. Linear Blending - After Effect", 1);
	imshow("3. Linear Blending - After Effect", dstImage);

	return 1;

	system("pause");
}

//---------------------------------ROI_LinearBlending-------------------------------------  
// Name: ROI_LinearBlending()
// Date: 11/18/2015
// Blend two images linearly
//--------------------------------------------------------------------------------------------  
bool ROI_LinearBlending()
{

	// Load Image fromm File
	Mat srcImage4 = imread("eva_origin.jpg", 1);
	Mat Image_logo = imread("eva_logo.jpg");

	if (!srcImage4.data) 
	{ 
		printf("Cannot load image! Error Window 4 \n"); 
		return 0; 
	}
	if (!Image_logo.data) 
	{ 
		printf("Cannot load image logo! Error Window 4 \n"); 
		return 0; 
	}

	// Select ROI 
	Mat imageROI;
	imageROI = srcImage4(Rect(0, 0, Image_logo.cols, Image_logo.rows));
	 
	
	// Add logo to original pic  
	addWeighted(imageROI, 0.5, Image_logo, 0.5, 0., imageROI);

	// Display Effect
	namedWindow("4. Linear Blending Effect - EVA");
	imshow("4. Linear Blending Effect - EVA", srcImage4);

	return 1;
	system("pause");
}
