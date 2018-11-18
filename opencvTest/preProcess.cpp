#include"common.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<iostream>
#include<cstdio>
using namespace cv;
using namespace std;
Mat preProc(Mat img_src, double size = 15, bool testflag = true)//img_src=传进来的图, size=腐蚀大小,简单来说SIZE越大腐蚀后的区域越小,testflag是否输出中间腐蚀图像和原图对比
{
	Mat stdImg;
	resize(img_src, stdImg, Size(300, 300), 0, 0, INTER_LINEAR);
	Mat out;
	Mat element = getStructuringElement(MORPH_CROSS, Size(size, size));
	//进行腐蚀操作
	erode(stdImg, out, element);
	resize(out, out, img_src.size(), 0, 0, INTER_LINEAR);
	if (testflag) {
		namedWindow("原");
		//namedWindow("中");
		namedWindow("后");
		//显示原图
		imshow("原", img_src);
		//获取自定义核
		//显示效果图
		//imshow("中",stdImg);
		imshow("后", out);
	}
	return out;
}
Mat preProc1(Mat img_src, double size = 15, bool testflag = true)//img_src=传进来的图, size=腐蚀大小,简单来说SIZE越大腐蚀后的区域越小,testflag是否输出中间腐蚀图像和原图对比
{
	Mat stdImg;
	resize(img_src, stdImg, Size(300, 300), 0, 0, INTER_LINEAR);
	Mat out;
	Mat element = getStructuringElement(MORPH_CROSS, Size(size, size));

	dilate(stdImg, out, element);
	resize(out, out, img_src.size(), 0, 0, INTER_LINEAR);
	if (testflag) {
		namedWindow("原");
		//namedWindow("中");
		namedWindow("后");
		//显示原图
		imshow("原", img_src);
		//获取自定义核
		//显示效果图
		//imshow("中",stdImg);
		imshow("后", out);
	}
	return out;
}
bool isOver(int x, int y, Mat img)
{
	if (x < 0 || x >= img.rows)
	{
		return true;
	}
	if (y < 0 || y >= img.cols)
	{
		return true;
	}
	return false;
}
void deepSearch(int x, int y, int& sum, Mat img, Mat map)//map约定:0未搜过 1是临时 255是要 128是不要
{
	if (sum > 100)
		return;
	if (map.at<uchar>(x, y) == 1)
		return;
	if (img.at<uchar>(x, y) == 255)//如果该点为白色
	{
		if (map.at<uchar>(x, y) == 0)//如果该点未被访问过
		{
			map.at<uchar>(x, y) = 1;
			sum++;
			if (!isOver(x + 1, y, img))
			{
				deepSearch(x + 1, y, sum, img, map);
			}
			if (!isOver(x - 1, y, img))
			{
				deepSearch(x - 1, y, sum, img, map);
			}
			if (!isOver(x, y + 1, img))
			{
				deepSearch(x, y + 1, sum, img, map);
			}
			if (!isOver(x, y - 1, img))
			{
				deepSearch(x, y - 1, sum, img, map);
			}
			if (!isOver(x + 1, y - 1, img))
			{
				deepSearch(x + 1, y - 1, sum, img, map);
			}
			if (!isOver(x + 1, y + 1, img))
			{
				deepSearch(x + 1, y + 1, sum, img, map);
			}
			if (!isOver(x - 1, y + 1, img))
			{
				deepSearch(x - 1, y + 1, sum, img, map);
			}
			if (!isOver(x - 1, y - 1, img))
			{
				deepSearch(x - 1, y - 1, sum, img, map);
			}
		}
	}
}
void mark255(int x, int y, int& sum, Mat img, Mat &map)//map约定:0未搜过 255是要的点 128是不要的点
{
	if (img.at<uchar>(x, y) == 255)//如果该点为白色
	{
		if (map.at<uchar>(x, y) == 1)//如果该点是上次访问的
		{
			map.at<uchar>(x, y) = 255;
			sum++;
			if (!isOver(x + 1, y, img))
			{
				mark255(x + 1, y, sum, img, map);
			}
			if (!isOver(x - 1, y, img))
			{
				mark255(x - 1, y, sum, img, map);
			}
			if (!isOver(x, y + 1, img))
			{
				mark255(x, y + 1, sum, img, map);
			}
			if (!isOver(x, y - 1, img))
			{
				mark255(x, y - 1, sum, img, map);
			}
			if (!isOver(x + 1, y - 1, img))
			{
				mark255(x + 1, y - 1, sum, img, map);
			}
			if (!isOver(x + 1, y + 1, img))
			{
				mark255(x + 1, y + 1, sum, img, map);
			}
			if (!isOver(x - 1, y + 1, img))
			{
				mark255(x - 1, y + 1, sum, img, map);
			}
			if (!isOver(x - 1, y - 1, img))
			{
				mark255(x - 1, y - 1, sum, img, map);
			}
		}
	}
}
void mark128(int x, int y, int& sum, Mat img, Mat &map)//map约定:0未搜过 255是要的点 128是不要的点
{
	if (img.at<uchar>(x, y) == 255)//如果该点为白色
	{
		if (map.at<uchar>(x, y) == 1)//如果该点是上次访问的
		{
			map.at<uchar>(x, y) = 128;
			sum++;
			if (!isOver(x + 1, y, img))
			{
				mark128(x + 1, y, sum, img, map);
			}
			if (!isOver(x - 1, y, img))
			{
				mark128(x - 1, y, sum, img, map);
			}
			if (!isOver(x, y + 1, img))
			{
				mark128(x, y + 1, sum, img, map);
			}
			if (!isOver(x, y - 1, img))
			{
				mark128(x, y - 1, sum, img, map);
			}
			if (!isOver(x + 1, y - 1, img))
			{
				mark128(x + 1, y - 1, sum, img, map);
			}
			if (!isOver(x + 1, y + 1, img))
			{
				mark128(x + 1, y + 1, sum, img, map);
			}
			if (!isOver(x - 1, y + 1, img))
			{
				mark128(x - 1, y + 1, sum, img, map);
			}
			if (!isOver(x - 1, y - 1, img))
			{
				mark128(x - 1, y - 1, sum, img, map);
			}
		}
	}
}
Mat clearNoise(Mat img, int threshold)
{
	int row = img.rows;
	int col = img.cols;
	Scalar sc(0);
	Mat map(row, col, CV_8UC1, sc);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int sum = 0;
			int temp = 0;
			if (img.at<uchar>(i, j) != 0)
			{
				deepSearch(i, j, sum, img, map);
				if (sum >= threshold)
				{
					mark255(i, j, temp, img, map);
				}
				else
				{
					mark128(i, j, temp, img, map);
				}
			}
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (map.at<uchar>(i, j) == 128)
				map.at<uchar>(i, j) = 0;
		}
	}
	return map;
}
Mat outerContours(Mat img)
{
	int row = img.rows;
	int col = img.cols;
	Scalar sc(0);
	Mat map(img.rows, img.cols, CV_8UC1, sc);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (img.at<uchar>(i, j) == 255)
			{
				map.at<uchar>(i, j) = 255;
				break;
			}
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = col - 1; j >= 0; j--)
		{
			if (img.at<uchar>(i, j) == 255)
			{
				map.at<uchar>(i, j) = 255;
				break;
			}
		}
	}
	for (int j = 0; j < col; j++)
	{
		for (int i = 0; i < row; i++)
		{
			if (img.at<uchar>(i, j) == 255)
			{
				map.at<uchar>(i, j) = 255;
				break;
			}
		}
	}
	for (int j = 0; j < col; j++)
	{
		for (int i = row - 1; i > 0; i--)
		{
			if (img.at<uchar>(i, j) == 255)
			{
				map.at<uchar>(i, j) = 255;
				break;
			}
		}
	}
	return map;
}
Mat addContours(Mat img, Mat map)
{
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			if (map.at<uchar>(i, j) == 255)
			{
				img.at<Vec3b>(i, j)[0] = 5;
				img.at<Vec3b>(i, j)[1] = 5;
				img.at<Vec3b>(i, j)[2] = 140;
			}
		}
	}
	return img;
}
void SearchContours(int x, int y, Mat img, Mat& map, int sum)//map约定:0未搜过 128已搜过的黑 255已搜过的白
{//待解决: 四周全被灰色访问 却不能进入inner
	//实际上是全被访问了
	//imshow("showS", map);
	//waitKey(1);
	if (map.at<uchar>(x,y)!=0)
	{
		return;
	}
	if (sum > 220)//防止爆堆栈
		return;
	if (img.at<uchar>(x, y) == 255)
	{
		map.at<uchar>(x, y) = 255;
		return;
	}
	if (img.at<uchar>(x, y) == 0)
	{
		map.at<uchar>(x, y) = 128;
	}


	if (!isOver(x + 1, y, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x + 1, y, img, map, sum + 1);
	}
	if (!isOver(x - 1, y, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x - 1, y, img, map, sum + 1);
	}
	if (!isOver(x, y + 1, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x, y + 1, img, map, sum + 1);
	}
	if (!isOver(x, y - 1, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x, y - 1, img, map, sum + 1);
	}
	if (!isOver(x + 1, y - 1, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x + 1, y - 1, img, map, sum + 1);
	}
	if (!isOver(x + 1, y + 1, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x + 1, y + 1, img, map, sum + 1);
	}
	if (!isOver(x - 1, y + 1, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x - 1, y + 1, img, map, sum + 1);
	}
	if (!isOver(x - 1, y - 1, img))
	{
		//map.at<uchar>(x, y) = 128;
		SearchContours(x - 1, y - 1, img, map, sum + 1);
	}
}
Mat FindMyContours(Mat img)
{
	//imwrite("C:/Users/Administrator/Desktop/img.jpg",img);
	Scalar sc(0);
	Mat map(img.rows, img.cols, CV_8UC1, sc);
	for (int i = 0, j = 0; i < img.rows; i++)
	{
		SearchContours(i, j, img, map, 0);
	}
	for (int i = 0, j = img.cols - 1; i < img.rows; i++)
	{
		SearchContours(i, j, img, map, 0);
	}
	for (int i = 0, j = 0; j < img.cols; j++)
	{
		SearchContours(i, j, img, map, 0);
	}
	for (int i = img.rows - 1, j = 0; j < img.cols; j++)
	{
		SearchContours(i, j, img, map, 0);
	}
	return map;
}
std::vector<cv::Point> findBiggestContour(cv::Mat binary_image)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	int largest_area = 0;
	int largest_contour_index = 0;

	cv::findContours(binary_image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour
		if (a > largest_area) {
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
		}
	}
	if (contours.empty())
		return vector<cv::Point>();
	return contours[largest_contour_index];
}

//std::vector<cv::Point> findBiggestContour(cv::Mat binary_image)
//{
//	std::vector<std::vector<cv::Point>> contours;
//
//	int largest_area = 0;
//	int largest_contour_index = 0;
//
//	cv::findContours(binary_image, contours, cv::noArray(), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
//
//	for (int i = 0; i < contours.size(); i++)
//	{
//		int a = contours[i].size();
//		if (a > largest_area) {
//			largest_area = a;
//			largest_contour_index = i;
//		}
//	}
//
//	return contours[largest_contour_index];
//}

void testBiggest(char *path)
{
	int thresh = 30;
	cv::Mat src = imread(path);
	cv::Mat result = src.clone();
	cv::Mat black(src.rows, src.cols, CV_8UC1,Scalar(0));
	cv::Mat gray;
	cv::cvtColor(src, gray, CV_BGR2GRAY);
	//mser(gray);
    cv::Mat binary;
	cv::threshold(gray, binary, 80, 255, cv::THRESH_BINARY);
	Canny(binary, binary, thresh, thresh * 2, 3);
	morphologyEx(binary,binary , MORPH_CLOSE, Mat(3, 3, CV_8U), Point(-1, -1), 3);
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
}
