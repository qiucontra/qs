#include "stdafx.h"
#include "tooltip.h"
#include "../option.h"

Tooltip::Tooltip(char * pszMsg)
{
	strcpy_s(m_szMessage, pszMsg);
#if defined PIXEL_256X128
	m_tRect.x = 40;
	m_tRect.width = SCREEN_WIDTH - 2*m_tRect.x;
	m_tRect.y = 28;
	m_tRect.height = SCREEN_HEIGHT - 2*m_tRect.y;
#elif defined PIXEL_128X64
	m_tRect.x = 10;
	m_tRect.width = SCREEN_WIDTH - 2*m_tRect.x;
	m_tRect.y = 8;
	m_tRect.height = SCREEN_HEIGHT - 2*m_tRect.y;
#endif
	m_pszBackup = (char *)calloc(m_tRect.width*m_tRect.height, sizeof(char));
}

Tooltip::~Tooltip()
{
	FREE(m_pszBackup);
}

void Tooltip::Show()
{
	//首先将当前显示的图像备份起来
	for (unsigned int i=0; i<(m_tRect.width); i++){
		for(unsigned int j=0; j<(m_tRect.height); j++){
			m_pszBackup[i+j*m_tRect.width] = Display::GetScreen()[(i+m_tRect.x)+(j+m_tRect.y)*SCREEN_WIDTH];
			Display::GetScreen()[i+m_tRect.x+(j+m_tRect.y)*SCREEN_WIDTH] = UNDISPLAY;
		}
	}
	//画框
	Display::DrawRectangle(m_tRect.x, m_tRect.y, m_tRect.width, m_tRect.height);
#if defined PIXEL_256X128
	Display::DrawRectangle(m_tRect.x+1, m_tRect.y+1, m_tRect.width-2, m_tRect.height-2);
#endif

	int fontW, fontH, len=strlen(m_szMessage)/2;
	Zimo::GetChsSize(FONT_MID, &fontW, &fontH);

	//计算中间位置显示MSG
	int x = (m_tRect.width - len * fontW)/2 + m_tRect.x;
	int y = (m_tRect.height - fontH)/2 + m_tRect.y;
#if defined PIXEL_256X128
	Display::PrintString(m_szMessage, x, y, FONT_MID);
#elif defined PIXEL_128X64
	Display::PrintString(m_szMessage, x, y, FONT_SMALL);
#endif
}

void Tooltip::Resume()
{
	for (unsigned int i=0; i<(m_tRect.width); i++){
		for(unsigned int j=0; j<(m_tRect.height); j++){
			Display::GetScreen()[i+m_tRect.x+(j+m_tRect.y)*SCREEN_WIDTH] = m_pszBackup[i+j*m_tRect.width];
		}
	}
}