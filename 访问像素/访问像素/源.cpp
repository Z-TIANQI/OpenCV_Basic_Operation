#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//void RGB_Detection(Mat);
//void Uniformity_Detection(Mat);
void Distribution_Detection(Mat);

int main()
{
	Mat srcImage = imread("1.jpg");
	//RGB_Detection(srcImage);
	Distribution_Detection(srcImage);

	waitKey(0);
}

/*void RGB_Detection(Mat image)
{
	cout << "M=" << " " << image << endl << endl;
}

void Uniformity_Detection(Mat image)
{

}*/

void Distribution_Detection(Mat srcImage)
{
	int bins = 255;//特征空间子区段的数目
	int hist_size[] = { bins };
	float range[] = { 0,255 };
	const float* ranges[] = { range };
	Mat redHist, greenHist, blueHist;

	int channels_r[] = { 0 };
	calcHist(&srcImage,1,channels_r,Mat(),redHist,1,hist_size,ranges,true, false);

	int channels_g[] = { 1 };
	calcHist(&srcImage, 1, channels_g, Mat(),greenHist, 1, hist_size, ranges, true, false);

	int channels_b[] = { 2 };
	calcHist(&srcImage, 1, channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);

	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	int scale = 1;
	int histHeight = 256;
	Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);

	for (int i = 0; i < bins; i++)
	{
		float binValue_red = redHist.at<float>(i);
		float binValue_green = greenHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);
		int intensity_red = cvRound(binValue_red*histHeight / maxValue_red);
		int intensity_green = cvRound(binValue_green*histHeight / maxValue_green);
		int intensity_blue = cvRound(binValue_blue*histHeight / maxValue_blue);

		rectangle(histImage,
			Point(i*scale, histHeight - 1),
			Point((i + 1)*scale, histHeight - intensity_red),
			Scalar(255, 0, 0));

		rectangle(histImage,
			Point(i*scale, histHeight - 1),
			Point((i + bins + 1)*scale - 1, histHeight - intensity_green),
			Scalar(0, 255, 0));

		rectangle(histImage,
			Point((i+bins*2)*scale, histHeight - 1),
			Point((i + bins*2 + 1)*scale - 1, histHeight - intensity_blue),
			Scalar(0, 0, 255));
	}

	imshow("图像的RGB直方分布图", histImage);
}