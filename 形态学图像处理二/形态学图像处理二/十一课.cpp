#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat img1, img2;
int elementshape = MORPH_RECT;
int max1 = 10;
int openclose = 0;
int erodedilate = 0;
int tophatblackhat = 0;

static void on_openclose(int, void*);
//static void on_erodedilate(int, void*);
//static void on_tophatblackhat(int, void*);
static void showhelptext();

int main()
{
	system("color 2F");

	showhelptext();

	img1 = imread("1.jpg");
	if (!img1.data)
	{
		printf("����");
		return false;
	}

	namedWindow("ԭͼ");
	imshow("ԭͼ", img1);

	namedWindow("��������", 1);
	//namedWindow("���͸�ʴ", 1);
	//namedWindow("��ñ��ñ", 1);

	openclose = 9;
	//erodedilate = 9;
	//tophatblackhat = 2;

	createTrackbar("����ֵ", "��������", &openclose, max1 * 2 + 1, on_openclose);
	//createTrackbar("����ֵ", "���͸�ʴ", &erodedilate, max1 * 2 + 1, on_erodedilate);
	//createTrackbar("����ֵ", "��ñ��ñ", &tophatblackhat, max1 * 2 + 1, on_tophatblackhat);

	while (1);
	{
		int c;
		c = waitKey(0);

		on_openclose(openclose, 0);
		//on_erodedilate(erodedilate, 0);
		//on_tophatblackhat(tophatblackhat, 0);

		if ((char)c == 'q' || (char)c == 27)
			return(0);
		if ((char)c == 49)
			elementshape = MORPH_ELLIPSE;
		if ((char)c == 50)
			elementshape = MORPH_RECT;
		if ((char)c == 51)
			elementshape = MORPH_CROSS;
		if ((char)c == ' ')
			elementshape = (elementshape + 1) % 3;
	}

	return(0);
}

static void on_openclose(int, void*)
{
	int offset = openclose - max1;
	int absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(elementshape, Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1), Point(absolute_offset, absolute_offset));

	if (offset < 0)
		morphologyEx(img1, img2, MORPH_OPEN, element);
	else
		morphologyEx(img1, img2, MORPH_CLOSE, element);

	imshow("��������", img2);
}

/* static void on_erodedilate(int, void*)
{
	int offset = erodedilate - max1;
	int absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(elementshape, Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1), Point(absolute_offset, absolute_offset));

	if (offset < 0)
		morphologyEx(img1, img2, MORPH_ERODE, element);
	else
		morphologyEx(img1, img2, MORPH_DILATE, element);

	imshow("���͸�ʴ", img2);
}

static void on_tophatblackhat(int, void*)
{
	int offset = tophatblackhat - max1;
	int absolute_offset = offset > 0 ? offset : -offset;

	Mat element = getStructuringElement(elementshape, Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1), Point(absolute_offset, absolute_offset));

	if (offset < 0)
		morphologyEx(img1, img2, MORPH_TOPHAT, element);
	else
		morphologyEx(img1, img2, MORPH_TOPHAT, element);

	imshow("��ñ��ñ", img2);
}*/

static void showhelptext()
{ 
	printf("\n\n\n\t������������۲�ͼ��Ч��~\n\n");
	printf("\n\n\t��������˵��: \n\n"
		"\t\t���̰�����ESC�����ߡ�Q��- �˳�����\n"
		"\t\t���̰�����1��- ʹ����Բ(Elliptic)�ṹԪ��\n"
		"\t\t���̰�����2��- ʹ�þ���(Rectangle )�ṹԪ��\n"
		"\t\t���̰�����3��- ʹ��ʮ����(Cross-shaped)�ṹԪ��\n"
		"\t\t���̰������ո�SPACE��- �ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��\n"
		"\n\n\t\t\t\t\t\t\t\t by����"
	);
}