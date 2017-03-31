// 语言学习.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void Alarm()
{
	for (int i = 0; i < 10; i++)
	{
		cout << '\a';
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	char c = 65;
	// 变量t表示不可见的控制字符‘\t’，表示输出一个Tab控制
	char t = '\t';
	// 循环输出26个大写字母字符
	for (int i = 0; i < 26; ++i)
	{
		// 输出c所代表的字符
		cout << c << t;

		// 字符类型变量加1，使其成为ASCII表中的下一个字符
		c = c + 1;
	}

	wchar_t cChs = L'曾';
	// 设置wcout输出对象的区域并输出中文字符
	wcout.imbue(locale("chs"));
	wcout << cChs << endl;

	//
	// 定义一个string类型变量，表示英文字符串
	string strEn = "Good Morning!";
	// 定义一个wstring类型变量，表示中文字符串
	wstring strChs = L"陕A-82103";
	// 用cout输出string类型字符串
	// 用wcout输出wstring类型字符串
	cout << strEn;

	wcout.imbue(locale("chs")); // 设置区域

	wcout << strChs << endl;

	int N = 100;
	int *pa = &N;
	cout << N << " " << *pa<<" "<<pa << endl;


	while (true)
	{
		//获取系统时间
		SYSTEMTIME stLocal;
		GetLocalTime(&stLocal);

		if (7 == stLocal.wSecond)
		{
			Alarm();

			break;
		}
		else
		{
			Sleep(1000);
		}
	}

	int Waitcode = getchar();
	return 0;
}

