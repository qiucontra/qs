//#ifndef _DISPLAY_H_
//#define _DISPLAY_H_
#pragma once
#include "../option.h"
#include "zimo.h"

#if defined PIXEL_256X128
#define SCREEN_WIDTH		256
#define SCREEN_HEIGHT		128

#define	INFO_BAR_SIZE		24

#define TITLEBAR_AREA_X		0
#define TITLEBAR_AREA_Y		0
#define TITLEBAR_AREA_W		SCREEN_WIDTH
#define TITLEBAR_AREA_H		24

#define CHANNEL_SIZE		40
#define CHANNEL_AREA_X		0
#define CHANNEL_AREA_Y		TITLEBAR_AREA_H
#define CHANNEL_AREA_W		SCREEN_WIDTH
#define CHANNEL_AREA_H		(CHANNEL_SIZE*2)

#define OPTIONBAR_AREA_X	0
#define OPTIONBAR_AREA_Y	(SCREEN_HEIGHT - OPTIONBAR_SIZE)
#define OPTIONBAR_AREA_W	SCREEN_WIDTH
#define OPTIONBAR_AREA_H	24

#define CHANNEL1_SX			4
#define CHANNEL1_SY			(TITLE_BAR_SIZE + 4) 

#elif defined  PIXEL_128X64
#define SCREEN_WIDTH		128
#define SCREEN_HEIGHT		64

#define	INFO_BAR_SIZE		12

#define TITLEBAR_AREA_X		0
#define TITLEBAR_AREA_Y		0
#define TITLEBAR_AREA_W		SCREEN_WIDTH
#define TITLEBAR_AREA_H		16

#define CHANNEL_SIZE		24
#define CHANNEL_AREA_X		0
#define CHANNEL_AREA_Y		TITLEBAR_AREA_H
#define CHANNEL_AREA_W		SCREEN_WIDTH
#define CHANNEL_AREA_H		CHANNEL_SIZE

#define OPTIONBAR_AREA_X	0
#define OPTIONBAR_AREA_Y	(SCREEN_HEIGHT - OPTIONBAR_SIZE)
#define OPTIONBAR_AREA_W	SCREEN_WIDTH
#define OPTIONBAR_AREA_H	OPTIONBAR_SIZE

#define CHANNEL1_SX			2
#define CHANNEL1_SY			(TITLE_BAR_SIZE + 2) 
#endif

enum{
	UNDISPLAY = 0, //��ʾ
	DISPLAY = 1 //����ʾ
};

class Display
{
public:
	//��ɫȡ��
	static void Reverse(int x, int y, int w, int h);
	//��ͼ��
	static void DrawImage(int x, int y, int w, int h, unsigned int *buffer);
	//�����ο�
	static void DrawRectangle(int x, int y, int w, int h);
	//������
	static void DrawFullRect(int x, int y, int w, int h);
	//��ʾ�ַ�
	static void PrintChar(char ch, int x, int y, FONT_SIZE font);
	//��ʵASCII���ִ�
	static void PrintString(char *str, int x, int y, FONT_SIZE font);
	//��ʾ�����ִ�
	static void PrintChsChar(char *chs, int x, int y, FONT_SIZE font);
	//��Ļ��ʼ��
	static void Init(void){
		memset(Display::screen, UNDISPLAY, SCREEN_WIDTH*SCREEN_HEIGHT);
	}
	//�����Ļ
	static void Clear(int x=0, int y=0, int w=SCREEN_WIDTH, int h=SCREEN_HEIGHT){
		for (int i=0; i<w; i++){
			for (int j=0; j<h; j++){
				Display::screen[SCREEN_WIDTH*(y+j)+(x+i)] = UNDISPLAY;
			}
		}
	};
	//��ȡ��Ļ����
	static unsigned char *GetScreen(void){
		return screen;
	};
	//����Ļ������һ�������ɫ
	static void SetPixel(int x, int y, unsigned char color, unsigned pixel){
		for (unsigned int n=0; n<pixel; n++){
			for (unsigned int m=0; m<pixel; m++){
				screen[SCREEN_WIDTH*(y+n)+(x+m)] = color;
			}
		}
	};

private:
	static unsigned char screen[SCREEN_WIDTH*SCREEN_HEIGHT];
};
//#endif