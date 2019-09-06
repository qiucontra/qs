//#ifndef _OPTION_H_
//#define _OPTION_H_
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define PIXEL_128X64
#define PIXEL_256X128

#define KHZ		(1000)
#define MHZ		(1000*1000)
#define GHZ		(1000*1000*1000)

#define LOCAL_IP			"127.0.0.1"
#define LOCAL_PORT			8000

#define FREE(p)		do{if (p != NULL){free(p); p=NULL;}}while(0);	
#define DELETE_OBJ(obj)		do{if (obj != NULL){delete obj; obj=NULL;}}while(0);

enum
{
	OPER_UP = 0,
	OPER_DOWN,
	OPER_LEFT,
	OPER_RIGHT
};

enum
{
	KEY_0 = 0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_PWR,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_ENTER,
	KEY_BACK,
	KEY_MAX,
};

enum
{
	CHL_1 = 0,
	CHL_2,
	CHL_MAX
};

typedef struct rect_t
{
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
}RECT_T;

typedef enum{
	WND_INIT = 0, //初始化窗口
	WND_SELFTEST, //自检窗口 
	WND_MAIN, //主窗口
	WND_WAVESELECT, //波形选择加载窗口
	WND_WAVESET, //参数设置窗口
	WND_CALL, //通话窗口
	WND_MAX
}WND_TYPE;

typedef enum
{
	CTL_PROCESS = 0, //进度条控件
	CTL_TITLEBAR, //主题条控件
	CTL_OPTIONBAR, //功能条控件
	CTL_CHANNEL, //通道控件
	CTL_WAVESELECT, //波形选择控件
	CTL_WAVESET, //波形设置控件
	CTL_INPUT, //输入控件
	CTL_SELECT, //选择控件
	CTL_MAX
}CTL_TYPE;

#ifdef WIN32
#define STRCPY			strcpy_s
#define SPRINTF			sprintf_s
#else
#define STRCPY			strcpy
#define SPRINTF			sprintf
#define true			1
#define false			0
#define bool			int
#define __FUNCTION__	__func__
#endif

class Transfer
{
public:
	//十六进制转换为整型
	static int HexToInt(char * hex){
		int value=0, m=0, n=0, length=strlen(hex);
		for (m=0; m<length; m++){
			char c = hex[m];
			int multi = 1;
			if (c >= '0' && c <= '9'){
				c -= 0x30;
			}
			else if (c >= 'a' && c <= 'f'){
				c = c - 'a' + 10;
			}
			else if (c >= 'A' && c <= 'F'){
				c = c - 'A' + 10;
			}
			for (n=0; n<length-m-1; n++){
				multi *= 16;
			}
			value += (c*multi);
		}
		return value;
	};
	//将字传中的'a'~'f'转换为大写
	static void Strupr(char * hex){
		char a[] = "abcdef";
		char A[] = "ABCDEF";

		for (int i=0; i<(int)strlen(hex); i++){
			char c = hex[i];
			if (c >= 'a' && c <= 'f'){
				hex[i] = A[c - 'a'];
			}
		}
	}
};

//#endif