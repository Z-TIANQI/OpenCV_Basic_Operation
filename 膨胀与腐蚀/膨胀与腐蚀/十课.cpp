#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("1.jpg");
	namedWindow("ԭͼ");
	namedWindow("Ч��ͼ");
	imshow("ԭͼ", img);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat out;
	erode(img, out, element);

	imshow("Ч��ͼ", out);

	waitKey(0);
	return(0);
}