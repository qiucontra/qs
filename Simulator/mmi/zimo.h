//#ifndef _DISPLAY_H_
//#define _DISPLAY_H_
#pragma once
#include "../option.h"

typedef enum{
	FONT_MICRO = 0, //���壬�ߺţ�����
	FONT_MINI,
	FONT_SMALL, //���壬12�ţ�����
	FONT_MID, //���壬15�ţ�����
	FONT_LARGE,
}FONT_SIZE;

class Zimo
{
public:
	//��ȡ�����ַ���
	static unsigned char *GetChs(FONT_SIZE font);
	//��ȡ��������ĳ���
	static void GetChsSize(FONT_SIZE font, int *width, int *height);
	//��ȡASCII���ַ���
	static unsigned char *GetAsc(FONT_SIZE font);
	//��ȡASCII���ַ��ĳ���
	static void GetAscSize(FONT_SIZE font, int *width, int *height);
};
//#endif