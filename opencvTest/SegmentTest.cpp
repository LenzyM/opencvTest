//
//#include<opencv2\core\core.hpp>
//#include<opencv2\highgui\highgui.hpp>
//#include<opencv2\imgproc\imgproc.hpp>
//#include<iostream>
//
//using namespace cv;
//using namespace std;
//
//
////方法1
//void Contours1(Mat &image)
//{
//
//	//将image由彩色图像转换成灰度图像
//	cvtColor(image, image, CV_RGB2GRAY);
//	//再通过阈值函数将其转换为二值图像
//	threshold(image, image, 160, 255, THRESH_BINARY);//设置阈值为160，最大像素值为255
//	vector<vector<Point>> contours;
//	//find轮廓
//	findContours(image, contours, 1, CHAIN_APPROX_SIMPLE);
//	//draw轮廓
//	Mat result = Mat::zeros(image.size(), CV_8UC1);
//	if (!contours.empty())
//	{
//		//result:存放轮廓，contours：找到的轮廓，-1：将所有轮廓画出，Scalar(255)：由白色画，2：画笔粗细
//		drawContours(result, contours, -1, Scalar(255), 2);
//		imshow("处理图", result);
//	}
//
//}
//
////方法2
//void Contours2(Mat &image)
//{
//	Mat img1 = Mat::zeros(image.size(), CV_8UC1);
//	//将image由彩色图像转换成灰度图像
//	cvtColor(image, image, CV_RGB2GRAY);
//	//通过阈值函数将其转换为二值图像img1(大小与image一样，是单通道)
//	threshold(image, img1, 160, 255, THRESH_BINARY);//设置阈值为160，最大像素值为255
//	vector<vector<Point> >contours;//contours轮廓
//	vector<Vec4i> hierarchy;//hierarchy层次
//	//查找轮廓findContours
//	findContours(img1, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//	//初始化dst
//	Mat dst = Mat::zeros(image.size(), CV_8UC1);
//	//开始处理
//	if (!contours.empty() && !hierarchy.empty())
//	{	//循环轮廓数
//		for (int i = 0; i < contours.size(); i++)
//		{
//			//循环当前轮廓下的每一个点，contours[i].size()是当前轮廓下的总点数
//			for (int j = 0; j < contours[i].size(); j++)
//			{
//				Point p = Point(contours[i][j].x, contours[i][j].y);
//				//给当前轮廓下的每个点设置白色
//				dst.at<uchar>(p) = 255;
//			}
//			//drawContours绘制填充当前的轮廓i
//			drawContours(img1, contours, i, Scalar(255), 1, 8, hierarchy);
//
//		}
//	}
//	imshow("处理图", dst);
//}
//
////方法3
//void Contours3(Mat &image)
//{
//	Mat img;
//	GaussianBlur(image, img, Size(3, 3), 0);
//	Canny(img, img, 100, 250);
//	//定义点和向量
//	vector<vector<Point> >contours;//contours轮廓
//	vector<Vec4i> hierarchy;//hierarchy层次
//	//查找轮廓findContours
//	//参数1：为二值图像，可以是灰度图像，一般是经过Canny,拉普拉斯等边缘检测算子处理过的二值图像
//	//参数2：contours是一个双向的向量，向量内每个元素保存了一组由连续Point点构成的点集合向量，
//	//-------每一组点集就是一个轮廓，有多少轮廓contours就有多少元素
//	//参数3：hierarchy向量中每一个元素包含了4个int变量:hierarchy[i][0]~hierarchy[i][3]分别表示第i个轮廓的后一个，前一个，父，内嵌轮廓
//	//-------hierarchy向量内的元素和contours轮廓向量内的元素是一一对应的，向量的容量相同。
//	//参数4：定义轮廓的检索模式
//	//参数5：定义轮廓的近似方法
//	//参数6：Point偏移量，所有轮廓信息相对于原始图像对应点的偏移量
//	findContours(img, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//	//初始化dst
//	Mat dst = Mat::zeros(img.size(), CV_8UC1);
//	//开始处理
//	if (!contours.empty() && !hierarchy.empty())
//	{
//		for (int i = 0; i < contours.size(); i++)
//		{
//			for (int j = 0; j < contours[i].size(); j++)
//			{
//
//				Point p = Point(contours[i][j].x, contours[i][j].y);
//				dst.at<uchar>(p) = 255;
//			}
//			//绘制填充轮廓
//			drawContours(img, contours, i, Scalar(255), 1, 8, hierarchy);
//
//		}
//	}
//	imshow("处理图", dst);
//
//}
//
////方法4
//void Contours4(Mat &img)
//{
//
//	//将image由彩色图像转换成灰度图像
//	cvtColor(img, img, CV_RGB2GRAY);//CV_RGB2GRAY
//	//通过阈值转换成二值图像 
//	int threshval = 160;
//	Mat bw = (threshval < 128) ? (img < threshval) : (img > threshval);
//	vector<vector<Point>> contours;
//	//find轮廓
//	findContours(bw, contours, 1, CHAIN_APPROX_SIMPLE);
//	//draw轮廓
//	Mat result = Mat::zeros(img.size(), CV_8UC1);
//	if (!contours.empty())
//	{
//		//result:存放轮廓，contours：找到的轮廓，-1：将所有轮廓画出，Scalar(255)：由白色画，2：画笔粗细
//		drawContours(result, contours, -1, Scalar(255), 2);
//		imshow("处理图", result);
//	}
//}
//
//int main()
//{
//	Mat img = imread("C:/Users/86563/Desktop/UAV Pic/1.jpg");
//
//	namedWindow("1");
//	imshow("1", img);
//
//	//创建处理窗口
//	namedWindow("处理图");
//	Contours1(img);//方法1 
////	Contours2(img);//方法2
//	Contours3(img);//方法3
////Contours4(img);//方法4
//	waitKey();
//	return 0;
//}
#include"common.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<iostream>
#include<cstdio>
using namespace cv;
using namespace std;

Mat src, src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void*);
void testfunc()
{
	for (int i = 1; i <= 6; i++)
	{
		// 读图
		char path[255];
		sprintf(path, "C:/Users/Administrator/Desktop/AboutCV/carPic/test%d.jpg", i);
		src = imread(path, IMREAD_COLOR);
		if (src.empty())
			return;

		// 转化为灰度图
		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		blur(src_gray, src_gray, Size(3, 3));

		// 显示
		namedWindow("Source", WINDOW_AUTOSIZE);
		imshow("Source", src);

		// 滑动条
		createTrackbar("Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);

		// 回调函数
		thresh_callback(0, 0);

		waitKey(0);
	}
}

// 回调函数
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// canny 边缘检测
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	imshow("canny1", canny_output);
	// 寻找轮廓
	findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	imwrite("C:/Users/Administrator/Desktop/testing.jpg", canny_output);
	imshow("canny2", canny_output);
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	imshow("canny3", canny_output);
	// 画出轮廓
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
	}
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

}
