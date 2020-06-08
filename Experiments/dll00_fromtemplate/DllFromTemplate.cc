#include "pch.h"
#include "DllFromTemplate.h"
#include <fmt/format.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

string rets; // this string isnt destroyed on func stack destroy

int add(int a, int b) {
	return a + b;
}

const char* emitStringPtr() {
	rets = "yeet";
	return rets.c_str();
}

const char* emitReusedStringObjPtr() {
	rets = "reused string !!!";
	return rets.c_str();
}

const char* emitStringAutoMarshal() {
	rets = "marshalled string";
	return rets.c_str();
}

void tryOpenCv() {
	Mat mat(250, 250, CV_8UC3);
	mat.setTo(Scalar(255, 0, 255));
	namedWindow("Display window", WINDOW_AUTOSIZE );
	imshow("Display window", mat);
	waitKey(0);
}