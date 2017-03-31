#pragma once
class Day3
{
public:
	Day3();
	~Day3();

	//第一步，显示一副图片
	void show(Mat &src);

	void showErode(Mat &src);

	void blurImage(Mat &src);

	void CannyImage(Mat &src);

};

