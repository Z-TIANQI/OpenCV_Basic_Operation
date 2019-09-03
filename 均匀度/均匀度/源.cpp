#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("1.jpg", 1);
	Mat outputImage = srcImage.clone();
	int R = 0, G = 0, B = 0, total_NUM = outputImage.cols*outputImage.rows;
	int B_Average[3] = { 0,0,0 };
	int G_Average[3] = { 0,0,0 };
	int R_Average[3] = { 0,0,0 };
	int min[3] = { 0,0,0 }, max[3] = { 0,0,0 };

	for (int i = 0; i < outputImage.rows; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i);
		for (int j = 0; j < outputImage.cols; j++)
		{
			if (outputImage.at<Vec3b>(i,j)[0] > 100 && outputImage.at<Vec3b>(i, j)[0] < 255 && outputImage.at<Vec3b>(i, j)[1] < 150 && outputImage.at<Vec3b>(i, j)[2] < 150)
			{
				B++;
				for (int b = 0; b < 3; b++)
					B_Average[b] += outputImage.at<Vec3b>(i, j)[b];
			}
			if (outputImage.at<Vec3b>(i, j)[1] > 100 && outputImage.at<Vec3b>(i, j)[1] < 255 && outputImage.at<Vec3b>(i, j)[0] < 150 && outputImage.at<Vec3b>(i, j)[2] < 150)
			{
				G++;
				for (int g = 0; g < 3; g++)
				{
					G_Average[g] += outputImage.at<Vec3b>(i, j)[g];
				}
			}
			if (outputImage.at<Vec3b>(i, j)[2] > 100 && outputImage.at<Vec3b>(i, j)[2] < 255 && outputImage.at<Vec3b>(i, j)[0] < 150 && outputImage.at<Vec3b>(i, j)[1] < 150)
			{
				R++;
				for (int r = 0; r < 3; r++)
				{
					R_Average[r] += outputImage.at<Vec3b>(i, j)[r];
				}
			}
			if ((double)outputImage.at<Vec3b>(i, j) > max)
				max[i] = (int)outputImage.at<Vec3b>(i, j);
		}
	}

	for (int b = 0; b < 3; b++)
		B_Average[b] = B_Average[b] / B;
	for (int g = 0; g < 3; g++)
		G_Average[g] = G_Average[g] / G;
	for (int r = 0; r < 3; r++)
		R_Average[r] = R_Average[r] / R;

	cout << "【蓝色比例】" << "" << B / total_NUM << " " << endl<<"【蓝色平均RGB值】 [";
	for (int i = 0; i < 3; i++)
		cout << B_Average[i] << ",";
	cout << "]" << endl;

	cout << "【绿色比例】" << "" << G / total_NUM << " " << endl << "【绿色平均RGB值】 [";
	for (int i = 0; i < 3; i++)
		cout << G_Average[i] << ",";
	cout << "]" << endl;

	cout << "【红色比例】" << "" << R / total_NUM << " " << endl << "【红色平均RGB值】 [";
	for (int i = 0; i < 3; i++)
		cout << R_Average[i] << ",";
	cout << "]" << endl;

	cout << "其他颜色比例" << (total_NUM - G - B - R) / total_NUM << endl;

	system("pause");
	return 0;
}