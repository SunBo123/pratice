#include "stdafx.h"
#include "Day1.h"


Day1::Day1()
{
}


Day1::~Day1()
{

}

void Day1::show()
{
	/*Mat src = imread("1.png",1);
	resize(src,src,Size(640,480));
	imwrite("1.png",src);

	Mat src2 = imread("5.png", 1);
	resize(src2, src2, Size(640, 480));
	imwrite("5.png", src2);*/

	Mat src = imread("1.png", 1);
	namedWindow("IMG",1);
	imshow("IMG",src);

	Mat src2 = imread("5.png", 1);

	//感兴趣区域选择
	Mat ROI;
	Mat dst = imread("2.bmp",1);
	ROI = src2(Rect(100,100,dst.cols,dst.rows));
	dst.copyTo(ROI,dst);

	imshow("ROI",src2);


	//图像融合
	//computes weighted sum of two arrays (dst = alpha*src1 + beta*src2 + gamma)
	addWeighted(src,0.5,src2,0.5,0,src,-1);
	imshow("IMG2",src);

	waitKey(0);
}
//图像分离
void Day1::split1()
{
	Mat src = imread("1.png", 1);
	namedWindow("IMG", 1);
	imshow("IMG",src);

	Mat dst = imread("1.jpg",0);

	vector<Mat> channels;

	split(src,channels);

	Mat  imageBlueChannel;   
	imageBlueChannel = channels.at(0);
	Mat roi0 = imageBlueChannel(Rect(100, 100, dst.cols, dst.rows));
	addWeighted(roi0,1,dst,0.5,0,roi0);

	/*addWeighted(imageBlueChannel(Rect(100, 100, dst.cols, dst.rows)), 1.0,
		dst, 0.5, 0, imageBlueChannel(Rect(500, 250, dst.cols, dst.rows)));*/

	imshow("IMG0",imageBlueChannel);


	Mat  imageGreenChannel;
	imageGreenChannel = channels.at(1);
	Mat roi1 = imageGreenChannel(Rect(100, 100, dst.cols, dst.rows));
	addWeighted(roi1, 1, dst, 0.5, 0, roi1);

	/*addWeighted(imageGreenChannel(Rect(100, 100, dst.cols, dst.rows)), 1.0,
	dst, 0.5, 0, imageGreenChannel(Rect(500, 250, dst.cols, dst.rows)));*/

	imshow("IMG1", imageGreenChannel);


	Mat  imageRedChannel;
	imageRedChannel = channels.at(2);
	Mat roi2 = imageRedChannel(Rect(100, 100, dst.cols, dst.rows));
	addWeighted(roi2, 1, dst, 0.5, 0, roi2);

	/*addWeighted(imageRedChannel(Rect(100, 100, dst.cols, dst.rows)), 1.0,
	dst, 0.5, 0, imageRedChannel(Rect(500, 250, dst.cols, dst.rows)));*/

	imshow("IMG2", imageRedChannel);
	//
	merge(channels, src);
	imshow("After",src);


	waitKey(0);
}

Mat src1, dst1;
int g_nContrast; //对比度值  
int g_nBright;  //亮度值  
void ContrastAndBright(int, void *)
{

	//创建窗口  
	namedWindow("【原始图窗口】", 1);

	//三个for循环，执行运算 g_dstImage(i,j) =a*g_srcImage(i,j) + b  
	for (int y = 0; y < src1.rows; y++)
	{
		for (int x = 0; x < src1.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				dst1.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrast*0.01)*(src1.at<Vec3b>(y, x)[c]) + g_nBright);
			}
		}
	}

	//显示图像  
	imshow("【原始图窗口】", src1);
	imshow("【效果图窗口】", dst1);
}

//轨迹条调整亮度 对比度
void Day1::Trace()
{
	system("color5F");

	//读入用户提供的图像  
	src1 = imread("1.png");
	if (!src1.data) 
	{ 
		printf("Oh，no，读取g_srcImage图片错误~！\n"); 
	   //return false; 
	}
	dst1 = Mat::zeros(src1.size(), src1.type());

	//设定对比度和亮度的初值  
	g_nContrast = 80;
	g_nBright = 80;

	//创建窗口  
	namedWindow("【效果图窗口】", 1);

	//创建轨迹条  
	createTrackbar("对比度：", "【效果图窗口】", &g_nContrast, 300, ContrastAndBright);
	createTrackbar("亮   度：", "【效果图窗口】", &g_nBright, 200, ContrastAndBright);

	//调用回调函数  
	ContrastAndBright(g_nContrast, 0);
	ContrastAndBright(g_nBright, 0);

	
	//按下“q”键时，程序退出  
	while (char(waitKey(1)) != 'q') {}

	waitKey(0);

}


