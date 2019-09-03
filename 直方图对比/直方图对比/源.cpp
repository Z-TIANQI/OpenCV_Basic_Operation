#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage_base, hsvImage_base;
	Mat srcImage_test1, hsvImage_test1;
	Mat srcImage_test2, hsvImage_test2;

	//��ȡ��׼��������������1����������2
	srcImage_base = imread("0.jpg", 1);
	srcImage_test1 = imread("1.jpg", 1);
	srcImage_test2 = imread("2.jpg", 1);

	//��ͼƬ��ȡһ������
	Mat baseROI = srcImage_base(Rect(2310, 2122, 198, 127));
	Mat test1ROI = srcImage_test1(Rect(2160, 2051, 198, 127));
	Mat test2ROI = srcImage_test2(Rect(2220, 2053, 198, 127));

	//RGB��ʽתΪHSV��ʽ
	cvtColor(baseROI, hsvImage_base, COLOR_BGR2HSV);
	cvtColor(test1ROI, hsvImage_test1, COLOR_BGR2HSV);
	cvtColor(test2ROI, hsvImage_test2, COLOR_BGR2HSV);

	int h_bins = 50, s_bins = 60;
	int histSize[] = { h_bins,s_bins };
	float h_ranges[] = { 0,256 };
	float s_ranges[] = { 0,180 };
	const float* ranges[] = { h_ranges,s_ranges };
	int channels[] = { 0,1 };

	MatND baseHist;
	MatND halfDownHist;
	MatND test1Hist;
	MatND test2Hist;

	//�������������HSVֱ��ͼ
	calcHist(&hsvImage_base, 1, channels, Mat(), baseHist, 2, histSize, ranges, true, false);
	normalize(baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat());
	calcHist(&hsvImage_test1, 1, channels, Mat(), test1Hist, 2, histSize, ranges, true, false);
	normalize(test1Hist, test1Hist, 0, 1, NORM_MINMAX, -1, Mat());
	calcHist(&hsvImage_test2, 1, channels, Mat(), test2Hist, 2, histSize, ranges, true, false);
	normalize(test2Hist, test2Hist, 0, 1, NORM_MINMAX, -1, Mat());

	//�Ƚ�����ֱ��ͼ
	double base_base = compareHist(baseHist, baseHist, 0);
	double base_test1 = compareHist(baseHist, test1Hist, 0);
	double base_test2 = compareHist(baseHist, test2Hist, 0);

	cout << "ƥ��������" << endl;
	cout << "����׼������ " << base_base << endl;
	cout << "����������1��" << base_test1 << endl;
	cout << "����������2��" << base_test2 << endl;

	system("pause");
	return 0;
}