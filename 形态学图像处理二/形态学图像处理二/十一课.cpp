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
		printf("出错");
		return false;
	}

	namedWindow("原图");
	imshow("原图", img1);

	namedWindow("开闭运算", 1);
	//namedWindow("膨胀腐蚀", 1);
	//namedWindow("顶帽黑帽", 1);

	openclose = 9;
	//erodedilate = 9;
	//tophatblackhat = 2;

	createTrackbar("迭代值", "开闭运算", &openclose, max1 * 2 + 1, on_openclose);
	//createTrackbar("迭代值", "膨胀腐蚀", &erodedilate, max1 * 2 + 1, on_erodedilate);
	//createTrackbar("迭代值", "顶帽黑帽", &tophatblackhat, max1 * 2 + 1, on_tophatblackhat);

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

	imshow("开闭运算", img2);
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

	imshow("膨胀腐蚀", img2);
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

	imshow("顶帽黑帽", img2);
}*/

static void showhelptext()
{ 
	printf("\n\n\n\t请调整滚动条观察图像效果~\n\n");
	printf("\n\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】或者【Q】- 退出程序\n"
		"\t\t键盘按键【1】- 使用椭圆(Elliptic)结构元素\n"
		"\t\t键盘按键【2】- 使用矩形(Rectangle )结构元素\n"
		"\t\t键盘按键【3】- 使用十字型(Cross-shaped)结构元素\n"
		"\t\t键盘按键【空格SPACE】- 在矩形、椭圆、十字形结构元素中循环\n"
		"\n\n\t\t\t\t\t\t\t\t by天琪"
	);
}