#include"common.h"
#include<iostream>
#include<cstdio>
using namespace cv;
using namespace std;
void detectContours(char* path, int thresh)
{
	Mat src_gray = imread(path);
	Mat origin = src_gray;
	cvtColor(src_gray, src_gray, CV_BGR2GRAY);//2gray
	//imshow("gray", src_gray);
	//waitKey(0);
	threshold(src_gray, src_gray, 80, 255, CV_THRESH_BINARY);//2binary image
	//imshow("bin", src_gray);
	//waitKey(0);
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// canny ±ßÔµ¼ì²â
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	//imshow("cannyºó", canny_output);
	//waitKey(0);
	//canny_output=preProc(canny_output,2,false);
	//imshow("proc", canny_output);
	//waitKey(0);
	//canny_output = preProc1(canny_output, 2, false);
	//imshow("proc1", canny_output);
	//waitKey(0);
	Scalar sc(0);
	Mat map(canny_output.rows, canny_output.cols, CV_8UC1, sc);
	//imwrite("C:/Users/Administrator/Desktop/source.jpg", canny_output);
	canny_output=clearNoise(canny_output, 40);
	
	imshow("clearNoise", canny_output);
	waitKey(0);

	int lasti = 0;
	int lastj = 0;
	for (int i = 0; i < canny_output.rows; i++)
	{
		for (int j = 0; j < canny_output.cols; j++)
		{
			if (canny_output.at<uchar>(i, j) > 50)//is canny point (white)
			{
				if (!(lasti == 0 && lastj == 0))
				{
					//line(map, Point(lasti, lastj), Point(i, j), Scalar(255));
					line(map, Point(lastj, lasti), Point(j, i), Scalar(255));
					//imshow("point", map);
					//waitKey(10);
				}
				//map.at<uchar>(i, j) = 10;
				lasti = i;
				lastj = j;
				break;
			}
		}
	}
	//imwrite("C:/Users/Administrator/Desktop/for1.jpg", map);
	lasti = 0, lastj = 0;
	for (int i = 0; i < canny_output.rows; i++)
	{
		for (int j = canny_output.cols - 1; j >= 0; j--)
		{
			if (canny_output.at<uchar>(i, j) > 50)//is canny point (white)
			{
				if (!(lasti == 0 && lastj == 0))
				{
					//line(map, Point(lasti, lastj), Point(i, j), Scalar(255));
					line(map, Point(lastj, lasti), Point(j, i), Scalar(255));
					//imshow("point", map);
					//waitKey(10);
				}
				//map.at<uchar>(i, j) = 10;
				lasti = i;
				lastj = j;
				break;
			}
		}
	}
	//imwrite("C:/Users/Administrator/Desktop/for2.jpg", map);
	lasti = 0, lastj = 0;
	for (int j = 0; j < canny_output.cols; j++)
	{
		for (int i = 0; i < canny_output.rows; i++)
		{
			if (canny_output.at<uchar>(i, j) > 50)//is canny point (white)
			{
				if (!(lasti == 0 && lastj == 0))
				{
					//line(map, Point(lasti, lastj), Point(i, j), Scalar(255));
					line(map, Point(lastj, lasti), Point(j, i), Scalar(255));
					//imshow("point", map);
					//waitKey(10);
				}
				//map.at<uchar>(i, j) = 10;
				lasti = i;
				lastj = j;
				break;
			}
		}
	}
	//imwrite("C:/Users/Administrator/Desktop/for3.jpg", map);
	lasti = 0, lastj = 0;
	for (int j = 0; j < canny_output.cols; j++)
	{
		for (int i = canny_output.rows - 1; i >= 0; i--)
		{
			if (canny_output.at<uchar>(i, j) > 50)//is canny point (white)
			{
				if (!(lasti == 0 && lastj == 0))
				{
					//line(map, Point(lasti, lastj), Point(i, j), Scalar(255));
					line(map, Point(lastj, lasti), Point(j, i), Scalar(255));
					//imshow("point", map);
					//waitKey(10);
				}
				//map.at<uchar>(i, j) = 10;
				lasti = i;
				lastj = j;
				break;
			}
		}
	}
	imwrite("C:/Users/Administrator/Desktop/for4.jpg", map);
	imshow("FOR4", map);
	waitKey(0);
	//map=outerContours(map);
	map = FindMyContours(map);
	imwrite("C:/Users/Administrator/Desktop/img.jpg", map);
	imshow("find", map);
	waitKey(0);
	//map=outerContours(map);
	//imshow("out", map);
	//waitKey(0);
	imwrite("C:/Users/Administrator/Desktop/forfinal.jpg", map);
	Mat finally = addContours(origin, map);
	imshow("finally", finally);
	waitKey(0);
	imwrite("C:/Users/Administrator/Desktop/finally.jpg", finally);
}