#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_grayImage;
int g_nThresh = 100;//��ֵ��ʼֵ
int g_nMaxThresh = 255;//��ֵ���ֵ
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;//����
vector<Vec4i> g_vHierarchy;//���

void on_ThreshChange(int, void*);//�ص��������ı���ֵ

int main()
{
	g_srcImage = imread("1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ
	blur(g_grayImage, g_grayImage, Size(3, 3));//����

	imshow("ԭʼͼ", g_srcImage);

	createTrackbar("��ֵ", "ԭʼͼ", &g_nThresh, g_nMaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return 0;
}

void on_ThreshChange(int ,void* )
{
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	//Ѱ������
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//�����
	vector<Moments>mu(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mu[i] = moments(g_vContours[i], false);
	}

	//��������
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
	}

	imshow("ͼ������", drawing);

	printf("\t ������ݣ��������������\n");
	for (unsigned int i = 0; i < g_vContours.size(); i++)
		printf("����[%d]�����=%.2f,���ȣ�%.2f \n\n", i, contourArea(g_vContours[i]), arcLength(g_vContours[i], true));
}
