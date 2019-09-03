#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

using namespace cv;

Mat g_srcImage, g_srcGrayImage, g_dstImage;
Mat g_srcImage1, g_srcGrayImage1, g_dstImage1;
Mat g_cannyDetectedEdges;
Mat g_cannyDetectedEdges1;
int g_cannyLowThreshold = 35;

static void on_Canny(int, void*);
static void on_Canny1(int, void*);

int main(int argc, char** argv)
{
	g_srcImage = imread("����ש��׼ͼ.jpg");
	g_srcImage1 = imread("���Ŵ�ש����-2.jpg");

	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_dstImage1.create(g_srcImage1.size(), g_srcImage1.type());
	cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);
	cvtColor(g_srcImage1, g_srcGrayImage1, COLOR_BGR2GRAY);
	createTrackbar("����ֵ��", "����ש��׼ͼ", &g_cannyLowThreshold, 120, on_Canny);
	on_Canny(g_cannyLowThreshold, 0);
	createTrackbar("����ֵ��", "���Ŵ�ש����", &g_cannyLowThreshold, 120, on_Canny1);
	on_Canny1(g_cannyLowThreshold, 0);

	Mat srcImage0 = imread("����ש��׼ͼ(Ч��ͼ).jpg");
	Mat srcImage1 = imread("���Ŵ�ש����(Ч��ͼ).jpg");
	Mat dstImage, dstImage1;

	addWeighted(srcImage0, 1, srcImage1, 0.5, 0.0, dstImage);
	namedWindow("����Ч��ͼ", WINDOW_NORMAL);
	cvtColor(dstImage, dstImage, COLOR_BGR2GRAY);
	equalizeHist(dstImage, dstImage1);
	imshow("����Ч��ͼ", dstImage1);
	imwrite("����Ч��ͼ.jpg", dstImage1);

	waitKey(0);
	return 0;
}

void on_Canny(int, void*)
{
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);
	g_dstImage = Scalar::all(0);

	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);
	imwrite("����ש��׼ͼ(Ч��ͼ).jpg", g_dstImage);
}

void on_Canny1(int, void*)
{
	blur(g_srcGrayImage1, g_cannyDetectedEdges1, Size(3, 3));
	Canny(g_cannyDetectedEdges1, g_cannyDetectedEdges1, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);
	g_dstImage1 = Scalar::all(255);

	g_srcImage1.copyTo(g_dstImage1, g_cannyDetectedEdges1);
	imwrite("���Ŵ�ש����(Ч��ͼ).jpg", g_dstImage1);
}