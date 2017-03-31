#include "stdafx.h"
#include "Day3.h"


Day3::Day3()
{
}


Day3::~Day3()
{
}
//��ʾͼƬ
void Day3::show(Mat &src)
{
	imshow("1",src);

	waitKey(0);
}
//ͼƬ��ʴ
void Day3::showErode(Mat &src)
{
	imshow("before",src);
	Mat dst;
	//��ȡ������
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));

	//��ʴ
	erode(src,dst,element);


	imshow("After",dst);

	waitKey(0);
 }

//ͼ���˲�
void Day3::blurImage(Mat &src)
{
	Mat dst;
	imshow("before",src);

	blur(src,dst,Size(5,5));

	imshow("After",dst);

	waitKey(0);
}

//ͼ���Ե���

void Day3::CannyImage(Mat &src)
{
	imshow("before",src);

	Mat dst, edge;

	cvtColor(src,dst,0);

	blur(dst,edge,Size(3,3));

	Canny(edge,edge,3,9,3);

	imshow("After",0);

	waitKey(0);
}
