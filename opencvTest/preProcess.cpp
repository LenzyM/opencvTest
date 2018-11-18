#include"common.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include<iostream>
#include<cstdio>
using namespace cv;
using namespace std;
Mat preProc(Mat img_src, double size = 15, bool testflag = true)//img_src=��������ͼ, size=��ʴ��С,����˵SIZEԽ��ʴ�������ԽС,testflag�Ƿ�����м丯ʴͼ���ԭͼ�Ա�
{
	Mat stdImg;
	resize(img_src, stdImg, Size(300, 300), 0, 0, INTER_LINEAR);
	Mat out;
	Mat element = getStructuringElement(MORPH_CROSS, Size(size, size));
	//���и�ʴ����
	erode(stdImg, out, element);
	resize(out, out, img_src.size(), 0, 0, INTER_LINEAR);
	if (testflag) {
		namedWindow("ԭ");
		//namedWindow("��");
		namedWindow("��");
		//��ʾԭͼ
		imshow("ԭ", img_src);
		//��ȡ�Զ����
		//��ʾЧ��ͼ
		//imshow("��",stdImg);
		imshow("��", out);
	}
	return out;
}
Mat preProc1(Mat img_src, double size = 15, bool testflag = true)//img_src=��������ͼ, size=��ʴ��С,����˵SIZEԽ��ʴ�������ԽС,testflag�Ƿ�����м丯ʴͼ���ԭͼ�Ա�
{
	Mat stdImg;
	resize(img_src, stdImg, Size(300, 300), 0, 0, INTER_LINEAR);
	Mat out;
	Mat element = getStructuringElement(MORPH_CROSS, Size(size, size));

	dilate(stdImg, out, element);
	resize(out, out, img_src.size(), 0, 0, INTER_LINEAR);
	if (testflag) {
		namedWindow("ԭ");
		//namedWindow("��");
		namedWindow("��");
		//��ʾԭͼ
		imshow("ԭ", img_src);
		//��ȡ�Զ����
		//��ʾЧ��ͼ
		//imshow("��",stdImg);
		imshow("��", out);
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
void deepSearch(int x, int y, int& sum, Mat img, Mat map)//mapԼ��:0δ�ѹ� 1����ʱ 255��Ҫ 128�ǲ�Ҫ
{
	if (sum > 100)
		return;
	if (map.at<uchar>(x, y) == 1)
		return;
	if (img.at<uchar>(x, y) == 255)//����õ�Ϊ��ɫ
	{
		if (map.at<uchar>(x, y) == 0)//����õ�δ�����ʹ�
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
void mark255(int x, int y, int& sum, Mat img, Mat &map)//mapԼ��:0δ�ѹ� 255��Ҫ�ĵ� 128�ǲ�Ҫ�ĵ�
{
	if (img.at<uchar>(x, y) == 255)//����õ�Ϊ��ɫ
	{
		if (map.at<uchar>(x, y) == 1)//����õ����ϴη��ʵ�
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
void mark128(int x, int y, int& sum, Mat img, Mat &map)//mapԼ��:0δ�ѹ� 255��Ҫ�ĵ� 128�ǲ�Ҫ�ĵ�
{
	if (img.at<uchar>(x, y) == 255)//����õ�Ϊ��ɫ
	{
		if (map.at<uchar>(x, y) == 1)//����õ����ϴη��ʵ�
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
void SearchContours(int x, int y, Mat img, Mat& map, int sum)//mapԼ��:0δ�ѹ� 128���ѹ��ĺ� 255���ѹ��İ�
{//�����: ����ȫ����ɫ���� ȴ���ܽ���inner
	//ʵ������ȫ��������
	//imshow("showS", map);
	//waitKey(1);
	if (map.at<uchar>(x,y)!=0)
	{
		return;
	}
	if (sum > 220)//��ֹ����ջ
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
