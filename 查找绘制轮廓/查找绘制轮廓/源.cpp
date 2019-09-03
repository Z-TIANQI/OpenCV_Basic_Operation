#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

vector<vector<Point>> contours;
vector<Vec4i> hierarchy;

int main()
{
	Mat srcImage = imread("1.jpg", 0);
	imshow("ԭʼͼ", srcImage);

	Mat dstImage = Mat::zeros(srcImage.cols, dstImage.rows, CV_8UC3);
	//srcImage = srcImage > 119;
	//imshow("ȡ��ֵ֮���ԭʼͼ", srcImage);

	//���Ƴ����ж��������
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	for (int index = 0; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
	}

	imshow("����ͼ", dstImage);
	waitKey(0);
	return 0;
}