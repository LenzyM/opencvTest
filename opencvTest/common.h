#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
//#include "opencv2/core/mat.hpp"
void testfunc();
void func(char*);
void funcThreshold(char* path);
void detectContours(char* path, int thresh);
cv::Mat preProc(cv::Mat img_src, double size, bool testflag);
cv::Mat preProc1(cv::Mat img_src, double size, bool testflag);
cv::Mat clearNoise(cv::Mat img, int threshold);
cv::Mat outerContours(cv::Mat img);
cv::Mat addContours(cv::Mat img, cv::Mat map);
cv::Mat FindMyContours(cv::Mat img);
void testBiggest(char *path);
void mser(cv::Mat gray);
std::string colorTest(cv::Mat img, cv::Mat map);
void test1();
typedef struct contourAndColor
{
	cv::Mat map;
	std::string color;
}ContourAndColor;