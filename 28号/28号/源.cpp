#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

#define WINDOW_NAME "【绘制图】"
#define WINDOW_WIDTH 600

void DrawEllipse(Mat, double);
void DrawFilledCircle(Mat, Point);

int main()
{
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	double time0 = static_cast<double>(getTickCount());

	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
	imshow( "绘制图",atomImage);

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "运行时间为" << time0 << "秒" << endl;

	waitKey(0);
	return 0;
}

void DrawEllipse(Mat img, double angle)
{
	int thickness=2;
	int lineType=8;

	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle,
		0,
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType);
}

void DrawFilledCircle(Mat img,Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center,
		WINDOW_WIDTH / 32,
		Scalar(0, 0, 255),
		thickness,
		lineType);
}