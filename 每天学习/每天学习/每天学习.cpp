// ÿ��ѧϰ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Day1.h"
#include "Day2.h"
#include "Day3.h"



int _tmain(int argc, _TCHAR* argv[])
{

	

	/*Day1 d1;
	d1.Trace();*/
	
	/*Day2 d2;
	d2.HoughtDetect();*/

	Day3 d3;
	Mat src = imread("1.jpg");
	d3.showErode(src);
	
	int charCode = getchar();

	waitKey(0);
	return 0;
}

