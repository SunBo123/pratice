#include "stdafx.h"
#include "Day2.h"


Day2::Day2()
{
}


Day2::~Day2()
{
}

void Day2::blur1()
{
	Mat src = imread("1.png",1);
	imshow("ԭͼ",src);
	Mat dst;
	dst.create(src.size(),src.type());
	dst = src.clone();

	//�����˲�
	//����
	boxFilter(src,dst,-1,Size(5,5));
	imshow("box",dst);

	//��ֵ
	blur(src,dst,Size(5,5));
	imshow("Meidin", dst);

	//��˹
	//sigmaX,X����ĵı�׼ƫ��,sigmaY Y����ĵı�׼ƫ��
	GaussianBlur(src,dst,Size(5,5),0,0);
	imshow("GAUSSIAN", dst);

	//������

	//��ֵ  �ߴ����Ϊ����
	medianBlur(src,dst,5);
	imshow("median", dst);

	//˫��
	bilateralFilter(src, dst, 25, 25 * 2, 25 / 2);
	imshow("bilateral", dst);

	waitKey(0);
}

void Day2::morphology()
{
	Mat src = imread("1.png", 1);

	imshow("ԭͼ", src);

	Mat dst;
	dst.create(src.size(), src.type());
	dst = src.clone();

	//�Զ����
	//��״�ɱ�
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat out;
	//����
	dilate(src, out, element);

	imshow("����",out);


	//��ʴ
	erode(src,out,element);
	imshow("��ʴ",out);

	//������
	morphologyEx(src, out, MORPH_OPEN,element);
	imshow("������",out);

	//������
	morphologyEx(src, out, MORPH_CLOSE, element);
	imshow("������", out);

	//��̬ѧ�ݶ�
	morphologyEx(src, out, MORPH_GRADIENT, element);
	imshow("��̬ѧ�ݶ�", out);

	//��ñ
	morphologyEx(src, out, MORPH_TOPHAT, element);
	imshow("��ñ����", out);

	//��ñ
	morphologyEx(src, out, MORPH_BLACKHAT, element);
	imshow("��ñ����", out);

	//��ʴ
	morphologyEx(src, out, MORPH_ERODE, element);
	imshow("��ʴ����", out);

	//����
	morphologyEx(src, out, MORPH_DILATE, element);
	imshow("��������", out);

	waitKey(0);
}
//��Ե���
int Day2::edgeDetect()
{
	Mat src = imread("1.png", 1);
	if (!src.data)
	{
		cout << "src is empty" << endl;
		return false;
	}
	imshow("ԭͼ", src);

	Mat dst;
	dst.create(src.size(), src.type());
	dst = src.clone();

	Canny(src,src,3,9,3);
	imshow("Ч��ͼ",src);

	//��ɫ��Եͼ
	Mat edge, gray;

	gray.create(src.size(), src.type());

	cvtColor(dst, gray, CV_BGR2GRAY);

	blur(gray, edge, Size(3, 3));

	Canny(dst, edge, 3, 9, 3);

	gray = Scalar::all(0);

	dst.copyTo(gray, edge);
	imshow("��ɫ��Ե",gray);

	/*cout << gray.channels() << endl;;
	cout << (int)gray.at<uchar>(100, 100);*/

	//Sobel

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,dst1;

	//��Ժ�Ϊ3ʱ�õ���׼ȷ�Ľ��
	Scharr(dst, grad_x,CV_16S,1,0);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("1", grad_x);

	Sobel(dst, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("x�����ݶ�",abs_grad_x);

	Sobel(dst, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y�����ݶ�", abs_grad_y);

	//�ϲ��ݶ�(����)  
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst1);
	imshow("���巽��Sobel", dst1);

	//Laplace
	Mat abs_dst;
	GaussianBlur(dst,dst1,Size(3,3),0,0);
	cvtColor(dst1,dst1,CV_BGR2GRAY);

	Laplacian(dst1,dst1,CV_16S,3,1,0);
	convertScaleAbs(dst1, abs_dst);
	imshow("Laplacian",abs_dst);


	waitKey(0);
}

int Day2::imageResize()
{
	Mat src = imread("1.png", 1);
	if (!src.data)
	{
		cout << "src is empty" << endl;
		return false;
	}
	imshow("ԭͼ", src);

	Mat dst;
	resize(src, dst, Size(200, 200), INTER_LINEAR);
	imshow("������ʾ",dst);

	pyrUp(src, dst, Size(src.cols * 2, src.rows * 2), BORDER_DEFAULT);
	imshow("�ϲ���", dst);

	pyrDown(src, dst, Size(src.cols/2, src.rows/2), BORDER_DEFAULT);
	imshow("�²���", dst);

	waitKey(0);
}

int Day2::HoughtDetect()
{
	Mat src = imread("1.png", 1);
	if (!src.data)
	{
		cout << "src is empty" << endl;
		return false;
	}
	imshow("ԭͼ", src);

	Mat midImage, dstImage;
	Canny(src,midImage,50,200,3);
	cvtColor(midImage, dstImage, CV_GRAY2BGR);
	imshow("��Ե�����", midImage);
	//
	vector<Vec2f> lines;
	//double���͵�rho��������Ϊ��λ�ľ��뾫��,theta �Ի���Ϊ��λ�ĽǶȾ���
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

	for (int i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}
	imshow("��Ч��ͼ��", dstImage);

	

	waitKey(0);
}