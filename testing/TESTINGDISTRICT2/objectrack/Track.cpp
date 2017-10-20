#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	cout<< "OpenCV " << CV_VERSION << endl
		<< "HSV Color range tool somewhere from the internet lol" << endl
		<< "by Plasmoxy ( Sebastian Petrik )" << endl
		<< "Press ESC or Q to exit." << endl
		;
	

	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam." << endl;
		return -1;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	resizeWindow("Control", 400, 400);

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	int morphScale = 5;
	int minSize = 30;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	cvCreateTrackbar("Morph scale", "Control", &morphScale, 5);
	cvCreateTrackbar("Minimal Size", "Control", &minSize, 100);

	while (true)
	{
		if (morphScale < 1) morphScale = 1;
		Mat imgOriginal;

		cap >> imgOriginal;
		/*
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video stream" << endl;
			break;
		}
		*/

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat mask;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), mask); //Threshold the image

		//morphological opening (remove small objects from the foreground)
		erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(morphScale, morphScale)));
		dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(morphScale, morphScale)));

		//morphological closing (fill small holes in the foreground)
		dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(morphScale, morphScale)));
		erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(morphScale, morphScale)));

		//combine mask with image
		Mat imgMasked;
		imgOriginal.copyTo(imgMasked, mask);

		// CONTOURS
		
		vector<vector<Point>> contours;
		findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		
		for (size_t idx = 0; idx < contours.size(); idx++)
		{
			drawContours(imgOriginal, contours, idx, Scalar(255, 0, 0));
			Rect contourRect = boundingRect(contours[idx]);
			if ( contourRect.height >= minSize || contourRect.width >= minSize)
				rectangle(imgOriginal, contourRect, Scalar(0, 0, 255), 2);
		}
		

		imshow("Masked image", imgMasked);
		imshow("Thresholded Image", mask); //show the thresholded image
		imshow("Original", imgOriginal); //show the original image

		int key = waitKey(30);
		if (key == 27 || key == (int)'q') //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;

}