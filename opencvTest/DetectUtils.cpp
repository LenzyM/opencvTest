#include"common.h"
using namespace cv;
int thresh = 30;
cv::Mat src = imread(path);
cv::Mat result = src.clone();
cv::Mat black(src.rows, src.cols, CV_8UC1, Scalar(0));
cv::Mat gray;
cv::cvtColor(src, gray, CV_BGR2GRAY);
//mser(gray);
cv::Mat binary;
cv::threshold(gray, binary, 80, 255, cv::THRESH_BINARY);
Canny(binary, binary, thresh, thresh * 2, 3);
morphologyEx(binary, binary, MORPH_CLOSE, Mat(3, 3, CV_8U), Point(-1, -1), 3);
//imshow("morp", binary);
//waitKey(0);
//clearNoise(src, 30);
std::vector< std::vector< cv::Point> > contours;
std::vector< cv::Point>  biggest_contour;
std::vector< std::vector< cv::Point> > temp_contours;
//cv::findContours(
//	binary,
//	contours,
//	cv::noArray(),
//	cv::RETR_LIST,
//	cv::CHAIN_APPROX_SIMPLE
//);
biggest_contour = findBiggestContour(binary);
temp_contours.push_back(biggest_contour);
//cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0));
cv::drawContours(black, temp_contours, 0, cv::Scalar(255));
//imshow("black", black);
//waitKey(0);
colorTest(src, black);
cv::drawContours(result, temp_contours, 0, cv::Scalar(0, 0, 255));
//cv::imshow("src", src);
//cv::imshow("gray", gray);
//cv::imshow("binary", binary);
cv::imshow("result", result);
cv::waitKey(0);
return;