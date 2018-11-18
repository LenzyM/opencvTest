#include"common.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;

void func(char* filenum)
{

	Mat img = imread(filenum);
	namedWindow("Source Image", 0);
	imshow("Source Image", img);
	//����һά������,��������ͼ�����ص�,ע��������ʽΪ32bit�������� 
	Mat samples(img.cols*img.rows, 1, CV_32FC3);
	//��Ǿ���32λ���� 
	Mat labels(img.cols*img.rows, 1, CV_32SC1);
	uchar* p;
	int i, j, k = 0;
	for (i = 0; i < img.rows; i++)
	{
		p = img.ptr<uchar>(i);
		for (j = 0; j < img.cols; j++)
		{
			samples.at<Vec3f>(k, 0)[0] = float(p[j * 3]);
			samples.at<Vec3f>(k, 0)[1] = float(p[j * 3 + 1]);
			samples.at<Vec3f>(k, 0)[2] = float(p[j * 3 + 2]);
			k++;
		}
	}

	int clusterCount = 2;
	Mat centers(clusterCount, 1, samples.type());
	kmeans(samples, clusterCount, labels,
		TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
		3, KMEANS_PP_CENTERS, centers);
	//������֪��3�����࣬�ò�ͬ�ĻҶȲ��ʾ�� 
	Mat img1(img.rows, img.cols, CV_8UC1);
	float step = 255 / (clusterCount - 1);
	k = 0;
	for (i = 0; i < img1.rows; i++)
	{
		p = img1.ptr<uchar>(i);
		for (j = 0; j < img1.cols; j++)
		{
			int tt = labels.at<int>(k, 0);
			k++;
			p[j] = 255 - tt * step;
		}
	}

	namedWindow("K-Means�ָ�Ч��", 0);
	imshow("K-Means�ָ�Ч��", img1);
	waitKey();
}