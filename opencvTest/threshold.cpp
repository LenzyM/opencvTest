#include"common.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src1, src1_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

void Threshold_Demo(int, void*);

void funcThreshold(char* path)
{
	// 读图
	src1 = imread(path, IMREAD_COLOR);
	if (src1.empty())
		return;

	// 转化为灰度图
	cvtColor(src1, src1_gray, COLOR_BGR2GRAY);
	// 显示窗口
	namedWindow(window_name, WINDOW_AUTOSIZE);
	// 滑动条 - 阈值化类型
	createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);
	// 滑动条 - 阈值
	createTrackbar(trackbar_value, window_name, &threshold_value, max_value, Threshold_Demo);

	Threshold_Demo(0, 0);

	waitKey(0);
}

void Threshold_Demo(int, void*)
{
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/
	threshold(src1_gray, dst, threshold_value, max_BINARY_value, threshold_type);
	imshow(window_name, dst);
}