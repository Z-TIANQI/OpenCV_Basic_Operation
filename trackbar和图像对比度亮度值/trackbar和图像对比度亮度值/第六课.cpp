#include<opencv2/core/core.hpp> 
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int g1, g2;
Mat img1, img2;

static void ContrastAndBright(int, void*);

int main()
{
	system("color5F");

	img1 = imread("pic1.jpg");
	if (!img1.data)
	{
		printf("����");
		return false;
	}
	img2 = Mat::zeros(img1.size(), img1.type());

	g1 = 80;
	g2 = 80;

	namedWindow("Ч��ͼ");

	createTrackbar("�Աȶ�", "Ч��ͼ", &g1, 300, ContrastAndBright);
	createTrackbar("����", "Ч��ͼ", &g2, 200, ContrastAndBright);

	ContrastAndBright(g1, 0);
	ContrastAndBright(g2, 0);

	waitKey(0);
	return(0);
}

	static void ContrastAndBright(int, void*)
	{
		namedWindow("��ԭʼͼ���ڡ�", 1);

		for (int y = 0; y < img1.rows; y++)
			for (int x = 0; x < img1.cols; x++)
				for (int c = 0; c < 3; c++)
					img1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g1*0.01)*(img1.at<Vec3b>(y, x)[c]) + g2);
		imshow("��ԭʼͼ���ڡ�", img1);
		imshow("��Ч��ͼ���ڡ�", img2);
	}

