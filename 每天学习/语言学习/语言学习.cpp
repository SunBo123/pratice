// ����ѧϰ.cpp : �������̨Ӧ�ó������ڵ㡣
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
	// ����t��ʾ���ɼ��Ŀ����ַ���\t������ʾ���һ��Tab����
	char t = '\t';
	// ѭ�����26����д��ĸ�ַ�
	for (int i = 0; i < 26; ++i)
	{
		// ���c��������ַ�
		cout << c << t;

		// �ַ����ͱ�����1��ʹ���ΪASCII���е���һ���ַ�
		c = c + 1;
	}

	wchar_t cChs = L'��';
	// ����wcout��������������������ַ�
	wcout.imbue(locale("chs"));
	wcout << cChs << endl;

	//
	// ����һ��string���ͱ�������ʾӢ���ַ���
	string strEn = "Good Morning!";
	// ����һ��wstring���ͱ�������ʾ�����ַ���
	wstring strChs = L"��A-82103";
	// ��cout���string�����ַ���
	// ��wcout���wstring�����ַ���
	cout << strEn;

	wcout.imbue(locale("chs")); // ��������

	wcout << strChs << endl;

	int N = 100;
	int *pa = &N;
	cout << N << " " << *pa<<" "<<pa << endl;


	while (true)
	{
		//��ȡϵͳʱ��
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

