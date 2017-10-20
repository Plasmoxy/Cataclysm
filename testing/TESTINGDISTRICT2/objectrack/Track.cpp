#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Scalar hsvBgrScalar(uchar H, uchar S, uchar V) {
	Mat rgb;
	Mat hsv(1, 1, CV_8UC3, Scalar(H, S, V));
	cvtColor(hsv, rgb, CV_HSV2BGR);
	return Scalar(rgb.data[0], rgb.data[1], rgb.data[2]);
}

int main(int argc, char** argv)
{
	cout<< "OpenCV " << CV_VERSION << endl
		<< "HSV Color range tool somewhere from the internet lol" << endl
		<< "by Plasmoxy ( Sebastian Petrik )" << endl
		<< "Written in C++" << endl
		<< "Press ESC or Q to exit." << endl
		;
	

	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam." << endl;
		return -1;
	}

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 50;
	int iHighS = 255;

	int iLowV = 35;
	int iHighV = 255;

	int morphScale = 5;
	int minSize = 30;

	int drawObjectRectangles = 1;
	int drawObjectContours = 0;

	namedWindow("Control", CV_WINDOW_AUTOSIZE);
	
	
	//Create trackbars in "Control" window
	cvCreateTrackbar("MinH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("MaxH", "Control", &iHighH, 179);

	cvCreateTrackbar("MinS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("MaxS", "Control", &iHighS, 255);

	cvCreateTrackbar("MinV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("MaxV", "Control", &iHighV, 255);

	cvCreateTrackbar("MorphSize", "Control", &morphScale, 20);
	cvCreateTrackbar("MinSize", "Control", &minSize, 500);

	cvCreateTrackbar("Rectangles", "Control", &drawObjectRectangles, 1);
	cvCreateTrackbar("Contours", "Control", &drawObjectContours, 1);

	// Window with current colors selected

	namedWindow("Colors", CV_WINDOW_NORMAL);
	resizeWindow("Colors", 300, 200);
	Mat colorMat(200, 200, CV_8UC3, Scalar(0, 0, 0));
	cvtColor(colorMat, colorMat, CV_BGR2HSV);

	

	while (true)
	{
		// draw the color rectangles
		rectangle(colorMat, Rect(0, 0, 100, 100), hsvBgrScalar(iLowH, iLowS, iLowV), -1);
		rectangle(colorMat, Rect(100, 0, 100, 100), hsvBgrScalar(iHighH, iHighS, iHighV), -1);
		
		rectangle(colorMat, Rect(0,100,100,100), hsvBgrScalar(iLowH, 255, 255), -1);
		rectangle(colorMat, Rect(100,100,100,100), hsvBgrScalar(iHighH, 255, 255), -1);
		
		putText(colorMat, "MIN", Point(0, 20), CV_FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 1);
		putText(colorMat, "MAX", Point(100, 20), CV_FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 1);

		putText(colorMat, "MIN_HUE", Point(0, 120), CV_FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 1);
		putText(colorMat, "MAX_HUE", Point(100, 120), CV_FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 1);

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
			if (drawObjectContours)
				drawContours(imgOriginal, contours, idx, Scalar(255, 0, 0));
			if (contourArea(contours[idx]) >= minSize*minSize)
			{
				Rect contourRect = boundingRect(contours[idx]);
				if (drawObjectRectangles)
				{
					rectangle(imgOriginal, contourRect, Scalar(0, 0, 255), 2);
				}
			}
		}

		imshow("Mask", mask);
		imshow("Masked image", imgMasked);
		imshow("Colors", colorMat);
		imshow("Original", imgOriginal); //show the original image with contours
		
		int key = waitKey(1); // one milisecond delay is good
		if (key == 27 || key == (int)'q')
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;

}