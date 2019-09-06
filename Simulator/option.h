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
	WND_INIT = 0, //��ʼ������
	WND_SELFTEST, //�Լ촰�� 
	WND_MAIN, //������
	WND_WAVESELECT, //����ѡ����ش���
	WND_WAVESET, //�������ô���
	WND_CALL, //ͨ������
	WND_MAX
}WND_TYPE;

typedef enum
{
	CTL_PROCESS = 0, //�������ؼ�
	CTL_TITLEBAR, //�������ؼ�
	CTL_OPTIONBAR, //�������ؼ�
	CTL_CHANNEL, //ͨ���ؼ�
	CTL_WAVESELECT, //����ѡ��ؼ�
	CTL_WAVESET, //�������ÿؼ�
	CTL_INPUT, //����ؼ�
	CTL_SELECT, //ѡ��ؼ�
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
	//ʮ������ת��Ϊ����
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
	//���ִ��е�'a'~'f'ת��Ϊ��д
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