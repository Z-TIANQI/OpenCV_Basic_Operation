#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_grayImage;
int g_nThresh = 100;//阈值初始值
int g_nMaxThresh = 255;//阈值最大值
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;//轮廓
vector<Vec4i> g_vHierarchy;//层次

void on_ThreshChange(int, void*);//回调函数，改变阈值

int main()
{
	g_srcImage = imread("1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//转化为灰度图
	blur(g_grayImage, g_grayImage, Size(3, 3));//降噪

	imshow("原始图", g_srcImage);

	createTrackbar("阈值", "原始图", &g_nThresh, g_nMaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}

void on_ThreshChange(int ,void* )
{
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	//寻找轮廓
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//计算矩
	vector<Moments>mu(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mu[i] = moments(g_vContours[i], false);
	}

	//绘制轮廓
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	imshow("图像轮廓", drawing);

	printf("\t 输出内容：面积与轮廓长度\n");
	for (unsigned int i = 0; i < g_vContours.size(); i++)
		printf("轮廓[%d]的面积=%.2f,长度：%.2f \n\n", i, contourArea(g_vContours[i]), arcLength(g_vContours[i], true));
}
