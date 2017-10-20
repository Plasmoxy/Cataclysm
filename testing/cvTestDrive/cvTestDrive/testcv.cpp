#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.jpg");
	imshow("lena", img);
	waitKey();

	return 0;
}