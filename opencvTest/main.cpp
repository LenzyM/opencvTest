#include"common.h"
#include<iostream>
int main()
{
	for (int i = 1; i <= 10; i++)
	{
		// ��ͼ
		char path[255];
		sprintf(path, "C:/Users/Administrator/Desktop/AboutCV/UAV Pic/%d.jpg", i);
		//detectContours(path, 50);
		//testBiggest(path);
		cv::Mat img=cv::imread(path);
		ContourAndColor cac;
		cac=ContourAndColorDetect(img);
		std::cout << cac.color << std::endl;
		cv::imshow("show", cac.map);
		getchar();

	}
	//for (int i = 1; i <= 6; i++)
	//{
	//	// ��ͼ
	//	char path[255];
	//	sprintf(path, "C:/Users/Administrator/Desktop/AboutCV/carPic/test%d.jpg", i);
	//	detectContours(path, 50);

	//	getchar();
	//}
	return 0;
}