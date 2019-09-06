#include "stdafx.h"
#include "process.h"

//modify by qiushi 2018-09-21
MyProcess::MyProcess(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHight, unsigned int nRange)
{
	m_tRect.x = nX;
	m_tRect.y = nY;
	m_tRect.width = nWidth;
	m_tRect.height = nHight;
	m_nRange = nRange;
	m_nPos = 0;
}

MyProcess::MyProcess(RECT_T rect, unsigned int range)
{
	MyProcess(rect.x, rect.y, rect.width, rect.height, range);
}

MyProcess::~MyProcess()
{
}

void MyProcess::Draw(void)
{
	int w = (m_nPos * m_tRect.width) / m_nRange;
	if (m_tRect.width < 3 || m_tRect.height < 3){
		//不符合进度条画图要求
		return;
	}
	Display::DrawRectangle(m_tRect.x, m_tRect.y, m_tRect.width, m_tRect.height);
	Display::DrawRectangle(m_tRect.x+1, m_tRect.y+1, m_tRect.width-2, m_tRect.height-2);
#ifdef PIXEL_256X128
	Display::DrawRectangle(m_tRect.x+2, m_tRect.y+2, m_tRect.width-4, m_tRect.height-4);
#endif
	Display::DrawFullRect(m_tRect.x, m_tRect.y, w, m_tRect.height);
}