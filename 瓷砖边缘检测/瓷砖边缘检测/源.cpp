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
	g_srcImage = imread("二号砖标准图.jpg");
	g_srcImage1 = imread("二号瓷砖裂纹-2.jpg");

	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_dstImage1.create(g_srcImage1.size(), g_srcImage1.type());
	cvtColor(g_srcImage, g_srcGrayImage, COLOR_BGR2GRAY);
	cvtColor(g_srcImage1, g_srcGrayImage1, COLOR_BGR2GRAY);
	createTrackbar("参数值：", "二号砖标准图", &g_cannyLowThreshold, 120, on_Canny);
	on_Canny(g_cannyLowThreshold, 0);
	createTrackbar("参数值：", "二号瓷砖裂纹", &g_cannyLowThreshold, 120, on_Canny1);
	on_Canny1(g_cannyLowThreshold, 0);

	Mat srcImage0 = imread("二号砖标准图(效果图).jpg");
	Mat srcImage1 = imread("二号瓷砖裂纹(效果图).jpg");
	Mat dstImage, dstImage1;

	addWeighted(srcImage0, 1, srcImage1, 0.5, 0.0, dstImage);
	namedWindow("最终效果图", WINDOW_NORMAL);
	cvtColor(dstImage, dstImage, COLOR_BGR2GRAY);
	equalizeHist(dstImage, dstImage1);
	imshow("最终效果图", dstImage1);
	imwrite("最终效果图.jpg", dstImage1);

	waitKey(0);
	return 0;
}

void on_Canny(int, void*)
{
	blur(g_srcGrayImage, g_cannyDetectedEdges, Size(3, 3));
	Canny(g_cannyDetectedEdges, g_cannyDetectedEdges, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);
	g_dstImage = Scalar::all(0);

	g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);
	imwrite("二号砖标准图(效果图).jpg", g_dstImage);
}

void on_Canny1(int, void*)
{
	blur(g_srcGrayImage1, g_cannyDetectedEdges1, Size(3, 3));
	Canny(g_cannyDetectedEdges1, g_cannyDetectedEdges1, g_cannyLowThreshold, g_cannyLowThreshold * 3, 3);
	g_dstImage1 = Scalar::all(255);

	g_srcImage1.copyTo(g_dstImage1, g_cannyDetectedEdges1);
	imwrite("二号瓷砖裂纹(效果图).jpg", g_dstImage1);
}