/*
LastModified:2018-8-19 23:32:16
Author:Siri Yang, Li Zhou
for the UAV color recognize project.
ver:1.0
*/
#include "opencv2/opencv.hpp"
#include<iostream>
#include<vector>
using namespace cv;
Mat fill(Mat img);
	std::string colorRecognize(Mat src_hsv, Mat map);
	int colorClass(int h, int s, int v);
	Mat eroBin(Mat img_src, double size = 15, bool testflag = false)//img_src=传进来的图, size=腐蚀大小,简单来说SIZE越大腐蚀后的区域越小,testflag是否输出中间腐蚀图像和原图对比
	{
			Mat stdImg;
			resize(img_src, stdImg,Size(300,300),0,0,INTER_LINEAR);
			Mat out;
			Mat element = getStructuringElement(MORPH_CROSS, Size(size,size));
			//进行腐蚀操作
			erode(stdImg, out, element);
			resize(out, out, img_src.size(),0,0,INTER_LINEAR);
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
	std::string colorClassString(int h, int s, int v,char language);
	void colorClassDemo()
	{
		Mat img = imread("D:\\VSProject\\opencvTest\\opencvTest\\resource\\img\\test\\testclass.jpg");
		Mat img_hsv;
		cvtColor(img, img_hsv, CV_BGR2HSV);
		std::vector<Mat> hsv;
		split(img_hsv, hsv);//将HSV三个通道分离
		for (int x = 0; x < img.rows; x++)
		{
			for (int y = 0; y < img.cols; y++)
			{
				//std::cout << map.at<uchar>(x, y) << std::endl;
				std::cout << colorClassString(hsv[0].at<uchar>(x, y), hsv[1].at<uchar>(x, y), hsv[2].at<uchar>(x, y),'c') << "  ";
			}
			std::cout << std::endl;
		}
	}
	std::string colorClassString(int h,int s,int v,char language='e')
	{
		int num = colorClass(h, s, v);
		if(language=='e')
		switch (num)
		{
		case 0:
			return "black";
			break;
		case 1:
			return "gray";
			break;
		case 2:
			return "white";
			break;
		case 3:
			return "red";
			break;
		case 4:
			return "orange";
			break;
		case 5:
			return "yellow";
			break;
		case 6:
			return "green";
			break;
		case 7:
			return "cyanine";
			break;
		case 8:
			return "blue";
			break;
		case 9:
			return "purple";
			break;
		default:
			break;
		}
		if (language == 'c')
		{
			switch (num)
			{
			case 0:
				return "黑";
				break;
			case 1:
				return "灰";
				break;
			case 2:
				return "白";
				break;
			case 3:
				return "红";
				break;
			case 4:
				return "橙";
				break;
			case 5:
				return "黄";
				break;
			case 6:
				return "绿";
				break;
			case 7:
				return "青";
				break;
			case 8:
				return "蓝";
				break;
			case 9:
				return "紫";
				break;
			default:
				break;
			}
		}
	}
	void colorRecTest() {
		//system("cls");
		//colorClassDemo();
		system("pause");
		for (int i = 14; i <= 17; i++) {
			char str[255];//原图路径
			char str_[255];//二值图路径
			sprintf(str, "D:\\VSProject\\opencvTest\\opencvTest\\resource\\img\\test\\%d.jpg", i);
			sprintf(str_, "D:\\VSProject\\opencvTest\\opencvTest\\resource\\img\\test\\%d_.jpg", i);
			Mat imgMap = imread(str_);//对Map的腐蚀操作在colorRecognize
			Mat img = imread(str);
			//imshow("test", img);
			std::cout << str << ": " << colorRecognize(img,imgMap) << std::endl;
			//waitKey(0);

			destroyAllWindows();
		}
	}
	std::string colorRecognize(Mat img, Mat map)// 
	{
		Mat src_hsv;
		cvtColor(img, src_hsv, CV_BGR2HSV);
		//分离通道
		std::vector<Mat> hsv;
		split(src_hsv, hsv);//将HSV三个通道分离
		//std::cout<< hsv[0].at<int>(0, 0)<<std::endl;
		int channels = src_hsv.channels();
		int nRows = src_hsv.rows;
		//图像数据列需要考虑通道数的影响；
		int nCols = src_hsv.cols * channels;
		int halfRow = nRows / 2;
		int halfCol = nCols / 2;
		//std::cout << nCols << " " << nRows << std::endl;

		if (src_hsv.isContinuous())//连续存储的数据，按一行处理
		{
			nCols *= nRows;
			halfCol *= nRows;
			nRows = 1;
			halfCol = 0;
		}
		
	//	std::cout << nCols << " " << nRows << std::endl;
		int colorArray[10] = { 0 };
		//map = eroBin(map,50,true);

			CvScalar scalar;	//scalar
			IplImage *image = new IplImage(map);
			for (int i = 0; i <= image->height - 1; ++i) {
				for (int j = 0; j <= image->width - 1; ++j) {
					scalar = cvGet2D(image, i, j);	//获取像素点的RGB颜色分量
					int control = 5;
				//if (scalar.val[2]>control&&scalar.val[0]>control&&scalar.val[1]>control)
					if(map.at<uchar>(i,j)==255)
							{
								colorArray[colorClass(hsv[0].at<uchar>(i, j), hsv[1].at<uchar>(i, j), hsv[2].at<uchar>(i, j))]++;
							}
				}
			}

		int colorMax = 0;
		//colorArray[0] = colorArray[0]*0.66;//降低黑色的为2/3, 之前是:手动降低灰色和黑色的权重为三分之二
		colorArray[1] = colorArray[1] * 0.66;
		for (int i = 0; i < 10; i++) {
			if (colorArray[i] > colorArray[colorMax]) {
				colorMax = i;
			}
		}
		for (int i : colorArray)//显示每个色彩统计量
			std::cout << i << std::endl;

		switch (colorMax)
		{
		case 0:
			return "black";
			break;
		case 1:
			return "gray";
			break;
		case 2:
			return "white";
			break;
		case 3:
			return "red";
			break;
		case 4:
			return "orange";
			break;
		case 5:
			return "yellow";
			break;
		case 6:
			return "green";
			break;
		case 7:
			return "cyanine";
			break;
		case 8:
			return "blue";
			break;
		case 9:
			return "purple";
			break;
		default:
			break;
		}

		return "";
			
		
	}
	std::string colorTest(Mat img,Mat map)
	{
		imshow("map", map);
		imshow("img", img);
		map = fill(map);
		std::string str = colorRecognize(img, map);
		std::cout<<str<<std::endl;
		return str;
	}
	int colorClass(int h, int s, int v) {
		/*
		黑：0
		灰：1
		白：2
		红：3
		橙：4
		黄：5
		绿：6
		青：7
		蓝：8
		紫：9
		*/

		if ((h >= 0 && h <= 180) && (s >= 0 && s <= 255) && (v >= 0 && v <= 46))//225->255
		{
			return 0;
		}
		else if ((h >= 0 && h <= 180) && (s >= 0 && s <= 43) && (v >= 46 && v <= 220))
		{
			return 1;
		}
		else if ((h >= 0 && h <= 180) && (s >= 0 && s <= 90) && (v >= 100 && v <= 255))//s的30放大
		//else if ((h >= 0 && h <= 180) && (s >= 0 && s <= 60) && (v >= 221 && v <= 255))//s的30放大 //v1
		{
			return 2;
		}
		else if (((h >= 0 && h <= 10) || (h >= 156 && h <= 180)) && (s >= 43 && s <= 255) && (v >= 46 && v <= 255))
		{
			return 3;
		}
		else if ((h >= 11 && h <= 25) && (s >= 43 && s <= 255) && (v >= 46 && v <= 255))
		{
			return 4;
		}
		else if ((h >= 26 && h <= 34) && (s >= 43 && s <= 255) && (v >= 46 && v <= 255))
		{
			return 5;
		}
		else if ((h >= 35 && h <= 77) && (s >= 43 && s <= 255) && (v >= 46 && v <= 255))
		{
			return 6;
		}
		else if ((h >= 78 && h <= 99) && (s >= 43 && s <= 255) && (v >= 46 && v <= 255))
		{
			return 7;
		}
		else if ((h >= 100 && h <= 124) && (s >= 43 && s <= 255) && (v >= 46 && v <= 255))
		{
			return 8;
		}
		else if ((h >= 125 && h <= 155) && (s >= 43 && s <= 255) && (v >= 46 && v <= 255))
		{
			return 9;
		}

		return 0;
	}
	Mat fillv1(Mat img)//黑背景 白线条
	{
		int row = img.rows;
		int col = img.cols;
		for (int j = 0; j < col; j++)
		{
			for (int i = 0; i < row; i++)
			{
				if (img.at<uchar>(i, j) == 255)
				{
					for (int x = i+1;x < row ; x++)
					{
						if (img.at<uchar>(x, j) == 255)
						{
							break;
						}
						img.at<uchar>(x, j) = 255;
					}
					break;
				}
			}
		}
		//for (int i = 0; i < row; i++)
		//{
		//	for (int j = 0; j < col; j++)
		//	{
		//		if (img.at<uchar>(i, j) == 255)
		//		{
		//			for (int y = j=1; y<col; y++)
		//			{
		//				if (img.at<uchar>(i, y) == 255)
		//				{
		//					break;
		//				}
		//				img.at<uchar>(i, y) = 255;
		//			}
		//			break;
		//		}
		//	}
		//}
		return img;
	}
	Mat fill(Mat img)
	{
		int row = img.rows;
		int col = img.cols;
		for (int j = 0; j < col; j++)
		{
			int breakflag = 0;
			int lastx = 0;
			while (lastx<row-1&&!breakflag)//万一下面还有可以连通的呢
			{

				int x1 = -1, x2 = -1;
				for (int i = lastx+1; i < row; i++)
				{
					if (img.at<uchar>(i, j) == 255 && img.at<uchar>(i + 1, j) != 255)
					{
						x1 = i;
						lastx = x1 + 1;
						for (int x = i + 1; x < row; x++)
						{
							if (img.at<uchar>(x, j) == 255 && img.at<uchar>(x+1, j) != 255)
							{
								x2 = x;
								lastx = x2 + 1;
								break;
							}
						}
						break;
					}
				}
				if (x1 != -1 && x2 != -1)
				{
					line(img, Point(j, x1), Point(j, x2), Scalar(255));
					imshow("imgline", img);
					waitKey(10);
				}
				else
				{
					breakflag = 1;
				}
			}
		}
		//for (int i = 0; i < row; i++)
		//{
		//	for (int j = 0; j < col; j++)
		//	{
		//		if (img.at<uchar>(i, j) == 255)
		//		{
		//			for (int y = j=1; y<col; y++)
		//			{
		//				if (img.at<uchar>(i, y) == 255)
		//				{
		//					break;
		//				}
		//				img.at<uchar>(i, y) = 255;
		//			}
		//			break;
		//		}
		//	}
		//}
		return img;
	}
//int main()
//{
////	colorRec::colorRecTest();
//for (int i = 1; i <= 6; i++)
//{
//	// 读图
//	char path[255];
//	sprintf(path, "C:/Users/86563/Desktop/carPic/test%d.jpg", i);
//	Mat src = imread(path, IMREAD_COLOR);
//
//	cvtColor(src, src, COLOR_BGR2GRAY);
//	threshold(src, src, 200,255,THRESH_BINARY);
//	colorRec::eroBin(src,5,true);
//
//
//	waitKey(0);
//}
//	return 0;
//}