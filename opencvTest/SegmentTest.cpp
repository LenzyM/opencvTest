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
////����1
//void Contours1(Mat &image)
//{
//
//	//��image�ɲ�ɫͼ��ת���ɻҶ�ͼ��
//	cvtColor(image, image, CV_RGB2GRAY);
//	//��ͨ����ֵ��������ת��Ϊ��ֵͼ��
//	threshold(image, image, 160, 255, THRESH_BINARY);//������ֵΪ160���������ֵΪ255
//	vector<vector<Point>> contours;
//	//find����
//	findContours(image, contours, 1, CHAIN_APPROX_SIMPLE);
//	//draw����
//	Mat result = Mat::zeros(image.size(), CV_8UC1);
//	if (!contours.empty())
//	{
//		//result:���������contours���ҵ���������-1������������������Scalar(255)���ɰ�ɫ����2�����ʴ�ϸ
//		drawContours(result, contours, -1, Scalar(255), 2);
//		imshow("����ͼ", result);
//	}
//
//}
//
////����2
//void Contours2(Mat &image)
//{
//	Mat img1 = Mat::zeros(image.size(), CV_8UC1);
//	//��image�ɲ�ɫͼ��ת���ɻҶ�ͼ��
//	cvtColor(image, image, CV_RGB2GRAY);
//	//ͨ����ֵ��������ת��Ϊ��ֵͼ��img1(��С��imageһ�����ǵ�ͨ��)
//	threshold(image, img1, 160, 255, THRESH_BINARY);//������ֵΪ160���������ֵΪ255
//	vector<vector<Point> >contours;//contours����
//	vector<Vec4i> hierarchy;//hierarchy���
//	//��������findContours
//	findContours(img1, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//	//��ʼ��dst
//	Mat dst = Mat::zeros(image.size(), CV_8UC1);
//	//��ʼ����
//	if (!contours.empty() && !hierarchy.empty())
//	{	//ѭ��������
//		for (int i = 0; i < contours.size(); i++)
//		{
//			//ѭ����ǰ�����µ�ÿһ���㣬contours[i].size()�ǵ�ǰ�����µ��ܵ���
//			for (int j = 0; j < contours[i].size(); j++)
//			{
//				Point p = Point(contours[i][j].x, contours[i][j].y);
//				//����ǰ�����µ�ÿ�������ð�ɫ
//				dst.at<uchar>(p) = 255;
//			}
//			//drawContours������䵱ǰ������i
//			drawContours(img1, contours, i, Scalar(255), 1, 8, hierarchy);
//
//		}
//	}
//	imshow("����ͼ", dst);
//}
//
////����3
//void Contours3(Mat &image)
//{
//	Mat img;
//	GaussianBlur(image, img, Size(3, 3), 0);
//	Canny(img, img, 100, 250);
//	//����������
//	vector<vector<Point> >contours;//contours����
//	vector<Vec4i> hierarchy;//hierarchy���
//	//��������findContours
//	//����1��Ϊ��ֵͼ�񣬿����ǻҶ�ͼ��һ���Ǿ���Canny,������˹�ȱ�Ե������Ӵ�����Ķ�ֵͼ��
//	//����2��contours��һ��˫���������������ÿ��Ԫ�ر�����һ��������Point�㹹�ɵĵ㼯��������
//	//-------ÿһ��㼯����һ���������ж�������contours���ж���Ԫ��
//	//����3��hierarchy������ÿһ��Ԫ�ذ�����4��int����:hierarchy[i][0]~hierarchy[i][3]�ֱ��ʾ��i�������ĺ�һ����ǰһ����������Ƕ����
//	//-------hierarchy�����ڵ�Ԫ�غ�contours���������ڵ�Ԫ����һһ��Ӧ�ģ�������������ͬ��
//	//����4�����������ļ���ģʽ
//	//����5�����������Ľ��Ʒ���
//	//����6��Pointƫ����������������Ϣ�����ԭʼͼ���Ӧ���ƫ����
//	findContours(img, contours, hierarchy, CV_RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//	//��ʼ��dst
//	Mat dst = Mat::zeros(img.size(), CV_8UC1);
//	//��ʼ����
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
//			//�����������
//			drawContours(img, contours, i, Scalar(255), 1, 8, hierarchy);
//
//		}
//	}
//	imshow("����ͼ", dst);
//
//}
//
////����4
//void Contours4(Mat &img)
//{
//
//	//��image�ɲ�ɫͼ��ת���ɻҶ�ͼ��
//	cvtColor(img, img, CV_RGB2GRAY);//CV_RGB2GRAY
//	//ͨ����ֵת���ɶ�ֵͼ�� 
//	int threshval = 160;
//	Mat bw = (threshval < 128) ? (img < threshval) : (img > threshval);
//	vector<vector<Point>> contours;
//	//find����
//	findContours(bw, contours, 1, CHAIN_APPROX_SIMPLE);
//	//draw����
//	Mat result = Mat::zeros(img.size(), CV_8UC1);
//	if (!contours.empty())
//	{
//		//result:���������contours���ҵ���������-1������������������Scalar(255)���ɰ�ɫ����2�����ʴ�ϸ
//		drawContours(result, contours, -1, Scalar(255), 2);
//		imshow("����ͼ", result);
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
//	//����������
//	namedWindow("����ͼ");
//	Contours1(img);//����1 
////	Contours2(img);//����2
//	Contours3(img);//����3
////Contours4(img);//����4
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
		// ��ͼ
		char path[255];
		sprintf(path, "C:/Users/Administrator/Desktop/AboutCV/carPic/test%d.jpg", i);
		src = imread(path, IMREAD_COLOR);
		if (src.empty())
			return;

		// ת��Ϊ�Ҷ�ͼ
		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		blur(src_gray, src_gray, Size(3, 3));

		// ��ʾ
		namedWindow("Source", WINDOW_AUTOSIZE);
		imshow("Source", src);

		// ������
		createTrackbar("Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);

		// �ص�����
		thresh_callback(0, 0);

		waitKey(0);
	}
}

// �ص�����
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// canny ��Ե���
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	imshow("canny1", canny_output);
	// Ѱ������
	findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	imwrite("C:/Users/Administrator/Desktop/testing.jpg", canny_output);
	imshow("canny2", canny_output);
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	imshow("canny3", canny_output);
	// ��������
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
	}
	namedWindow("Contours", WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

}
