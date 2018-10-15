#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat lena = imread("lena.jpg", -1);

	Mat lenainv;
	bitwise_not(lena, lenainv);
	
	line(lena, Point(0, 0), Point(50, 50), Scalar(0, 0, 255), 5, -1);

	imshow("lena", lena);
	imshow("lena inverted", lenainv);
	waitKey();
}