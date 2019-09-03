#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img1 = imread("dota_jugg.jpg", 1);
	Mat	img2 = imread("dota_logo.jpg", 0);
	Mat img3;
	vector<Mat>channels;
	if (!img1.data)
	{
		printf("出错");
		return false;
	}
	if (!img2.data)
	{
		printf("出错");
		return false;
	}
	split(img1,channels);
	img3 = channels.at(0);
	addWeighted(img3(Rect(500, 250, img2.cols, img2.rows)), 1.0, img2, 0.5,0., img3(Rect(500, 250, img2.cols, img2.rows)));
	merge(channels, img1);
	namedWindow("效果图");
	imshow("效果图", img1);
	waitKey(0);
	return(0);
}