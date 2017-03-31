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
	imshow("原图",src);
	Mat dst;
	dst.create(src.size(),src.type());
	dst = src.clone();

	//线性滤波
	//方框
	boxFilter(src,dst,-1,Size(5,5));
	imshow("box",dst);

	//均值
	blur(src,dst,Size(5,5));
	imshow("Meidin", dst);

	//高斯
	//sigmaX,X方向的的标准偏差,sigmaY Y方向的的标准偏差
	GaussianBlur(src,dst,Size(5,5),0,0);
	imshow("GAUSSIAN", dst);

	//非线性

	//中值  尺寸必须为奇数
	medianBlur(src,dst,5);
	imshow("median", dst);

	//双边
	bilateralFilter(src, dst, 25, 25 * 2, 25 / 2);
	imshow("bilateral", dst);

	waitKey(0);
}

void Day2::morphology()
{
	Mat src = imread("1.png", 1);

	imshow("原图", src);

	Mat dst;
	dst.create(src.size(), src.type());
	dst = src.clone();

	//自定义核
	//形状可变
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat out;
	//膨胀
	dilate(src, out, element);

	imshow("膨胀",out);


	//腐蚀
	erode(src,out,element);
	imshow("腐蚀",out);

	//开运算
	morphologyEx(src, out, MORPH_OPEN,element);
	imshow("开运算",out);

	//闭运算
	morphologyEx(src, out, MORPH_CLOSE, element);
	imshow("闭运算", out);

	//形态学梯度
	morphologyEx(src, out, MORPH_GRADIENT, element);
	imshow("形态学梯度", out);

	//顶帽
	morphologyEx(src, out, MORPH_TOPHAT, element);
	imshow("顶帽运算", out);

	//黑帽
	morphologyEx(src, out, MORPH_BLACKHAT, element);
	imshow("黑帽运算", out);

	//腐蚀
	morphologyEx(src, out, MORPH_ERODE, element);
	imshow("腐蚀运算", out);

	//膨胀
	morphologyEx(src, out, MORPH_DILATE, element);
	imshow("膨胀运算", out);

	waitKey(0);
}
//边缘检测
int Day2::edgeDetect()
{
	Mat src = imread("1.png", 1);
	if (!src.data)
	{
		cout << "src is empty" << endl;
		return false;
	}
	imshow("原图", src);

	Mat dst;
	dst.create(src.size(), src.type());
	dst = src.clone();

	Canny(src,src,3,9,3);
	imshow("效果图",src);

	//彩色边缘图
	Mat edge, gray;

	gray.create(src.size(), src.type());

	cvtColor(dst, gray, CV_BGR2GRAY);

	blur(gray, edge, Size(3, 3));

	Canny(dst, edge, 3, 9, 3);

	gray = Scalar::all(0);

	dst.copyTo(gray, edge);
	imshow("彩色边缘",gray);

	/*cout << gray.channels() << endl;;
	cout << (int)gray.at<uchar>(100, 100);*/

	//Sobel

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,dst1;

	//针对核为3时得到更准确的结果
	Scharr(dst, grad_x,CV_16S,1,0);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("1", grad_x);

	Sobel(dst, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("x方向梯度",abs_grad_x);

	Sobel(dst, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y方向梯度", abs_grad_y);

	//合并梯度(近似)  
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst1);
	imshow("整体方向Sobel", dst1);

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
	imshow("原图", src);

	Mat dst;
	resize(src, dst, Size(200, 200), INTER_LINEAR);
	imshow("缩放显示",dst);

	pyrUp(src, dst, Size(src.cols * 2, src.rows * 2), BORDER_DEFAULT);
	imshow("上采样", dst);

	pyrDown(src, dst, Size(src.cols/2, src.rows/2), BORDER_DEFAULT);
	imshow("下采样", dst);

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
	imshow("原图", src);

	Mat midImage, dstImage;
	Canny(src,midImage,50,200,3);
	cvtColor(midImage, dstImage, CV_GRAY2BGR);
	imshow("边缘处理后", midImage);
	//
	vector<Vec2f> lines;
	//double类型的rho，以像素为单位的距离精度,theta 以弧度为单位的角度精度
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
	imshow("【效果图】", dstImage);

	

	waitKey(0);
}