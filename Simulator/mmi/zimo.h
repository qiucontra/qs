//#ifndef _DISPLAY_H_
//#define _DISPLAY_H_
#pragma once
#include "../option.h"

typedef enum{
	FONT_MICRO = 0, //宋体，七号，粗体
	FONT_MINI,
	FONT_SMALL, //宋体，12号，粗体
	FONT_MID, //宋体，15号，粗体
	FONT_LARGE,
}FONT_SIZE;

class Zimo
{
public:
	//获取中文字符集
	static unsigned char *GetChs(FONT_SIZE font);
	//获取中文字体的长宽
	static void GetChsSize(FONT_SIZE font, int *width, int *height);
	//获取ASCII码字符集
	static unsigned char *GetAsc(FONT_SIZE font);
	//获取ASCII码字符的长宽
	static void GetAscSize(FONT_SIZE font, int *width, int *height);
};
//#endif