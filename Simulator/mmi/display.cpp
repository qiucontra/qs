#include "stdafx.h"
#include "display.h"

unsigned char Display::screen[SCREEN_WIDTH*SCREEN_HEIGHT];

void Display::Reverse(int x, int y, int w, int h)
{
	for (int j=0; j<h; j++){
		for (int i=0; i<w; i++){
			if (Display::screen[SCREEN_WIDTH*(y+j)+(x+i)] == DISPLAY){
				Display::screen[SCREEN_WIDTH*(y+j)+(x+i)] = UNDISPLAY;
			}
			else {
				Display::screen[SCREEN_WIDTH*(y+j)+(x+i)] = DISPLAY;
			}
		}
	}
}

void Display::PrintChar(char ch, int x, int y, FONT_SIZE font)
{
	int i=0,j=0;
	unsigned char *asc = Zimo::GetAsc(font);
	int width,height,step,start;

	Zimo::GetAscSize(font, &width, &height);

	if (font == FONT_MICRO){
		int size = font+1;
		for (i=0; i<width; i++){
			for (j=0; j<height; j++){
				int num = (ch - ' ') * width + i;
				char s = asc[num];
				if (((s >> j) & 0x01)  == 0x01){
					Display::SetPixel(x+size*i, y+size*j, DISPLAY, size);
				}
				else{
					Display::SetPixel(x+size*i, y+size*j, UNDISPLAY, size);
				}
			}
		}
		return;
	}

	step = ((width+7)/8);
	start = (ch - ' ')*(height*step);

	for (i=0; i<height*step; i+=step){
		unsigned int tmp;
		if (step == 1){
			tmp = asc[start+i] & 0x00FF;
		}
		else if (step == 2){
			tmp = ((asc[start+i] & 0x00FF)<<8) | (asc[start+i+1] & 0x00FF);
		}
		else if (step == 3){
			tmp = ((asc[start+i] & 0x00FF)<<16) | ((asc[start+i+1] & 0x00FF)<<8) | (asc[start+i+2] & 0x00FF);
		}
		
		for (j=0; j<width; j++){
			if (((tmp >> ((step*8)-j)) & 0x01)  == 0x01){
				Display::SetPixel(x+(j), y+i/step, DISPLAY, 1);
			}
			else {
				Display::SetPixel(x+(j), y+i/step, UNDISPLAY, 1);
			}
		}	
	}
}

void Display::PrintChsChar(char *ch, int x, int y, FONT_SIZE font)
{
	int i=0,j=0;
	unsigned char *chs = Zimo::GetChs(font);
	unsigned int display = UNDISPLAY;
	unsigned int h = (unsigned int)ch[0] & 0x00FF;
	unsigned int l = (unsigned int)ch[1] & 0x00FF;

	unsigned int offset = (h-0xB0)*188+(l-0xA1)*2;
	int width,height,step,start;

	Zimo::GetChsSize(font, &width, &height);
	step = ((width+7)/8);
	start = ((h-0xB0)*94+(l-0xA1))*(height*step);

	for (i=0; i<height*step; i+=step){
		unsigned int tmp;
		if (step == 1){
			tmp = chs[start+i] & 0x00FF;
		}
		else if (step == 2){
			tmp = ((chs[start+i] & 0x00FF)<<8) | (chs[start+i+1] & 0x00FF);
		}
		else if (step == 3){
			tmp = ((chs[start+i] & 0x00FF)<<16) | ((chs[start+i+1] & 0x00FF)<<8) | (chs[start+i+2] & 0x00FF);
		}
		
		for (j=0; j<width; j++){
			if (((tmp >> ((step*8)-j)) & 0x01)  == 0x01){
				Display::SetPixel(x+(j), y+i/step, DISPLAY, 1);
			}
			else {
				Display::SetPixel(x+(j), y+i/step, UNDISPLAY, 1);
			}
		}	
	}
}

void Display::PrintString(char *str, int x, int y, FONT_SIZE font)
{
	//ÅÐ¶Ï×Ö·ûÊÇ²»ÊÇÖÐÎÄ
	//GB2312 ·¶Î§£º 0xA1A1 - 0xFEFE ºº×Ö·¶Î§£º 0xB0A1 - 0xF7FE
	int width,height,offset = x;

	for (int i=0; i<(int)strlen(str); ){
		unsigned char ch = str[i] & 0x00FF;
		if (ch >= 0xB0){
			//ÖÐÎÄ×Ö·û
			Zimo::GetChsSize(font, &width, &height);
			Display::PrintChsChar(&str[i], offset, y, font);
			offset += width;		
			i += 2;
		}
		else {
			//acsiiÂë
			Zimo::GetAscSize(font, &width, &height);
			Display::PrintChar(str[i], offset, y, font);
			offset += width;
			i ++;
		}
	}
}

void Display::DrawImage(int x, int y, int w, int h, unsigned int *buffer)
{
	for (int i=0; i<w; i++){
		for (int j=0; j<h; j++){
			if (buffer[h*i+j] == 0xffffff){
				Display::screen[SCREEN_WIDTH*(y+j)+(x+i)] = DISPLAY;//DISPLAY;
			}
			else{
				Display::screen[SCREEN_WIDTH*(y+j)+(x+i)] = UNDISPLAY;//UNDISPLAY;
			}
		}
	}
}

void Display::DrawRectangle(int x, int y, int w, int h)
{
	int i=0, j=0;
	for (i=0; i<w; i++){
		Display::screen[SCREEN_WIDTH*(y)+(x+i)] = DISPLAY;
		Display::screen[SCREEN_WIDTH*(y+h-1)+(x+i)] = DISPLAY;
	}
	for (j=0; j<h; j++){
		Display::screen[SCREEN_WIDTH*(y+j)+(x)] = DISPLAY;
		Display::screen[SCREEN_WIDTH*(y+j)+(x+w-1)] = DISPLAY;	
	}
}

void  Display::DrawFullRect(int x, int y, int w, int h)
{
	for (int i=0; i<w; i++){
		for (int j=0; j<h; j++){
			Display::screen[SCREEN_WIDTH*(y+j)+(x+i)] = DISPLAY;
		}
	}
}