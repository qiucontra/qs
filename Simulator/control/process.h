//#ifndef _PROCESS_H_
//#define _PROCESS_H_
#pragma once
#include "../mmi/display.h"
#include "../option.h"

class MyProcess
{
public:
	MyProcess(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHight, unsigned int nRange);
	MyProcess(RECT_T nRect, unsigned int nRange);
	~MyProcess();
public:
	//设置当前的进度
	void SetPos(unsigned int nPos){
		m_nPos = nPos;
		Draw();
	};
	//获取控件的大小和位置
	RECT_T * GetRect(){
		return &m_tRect;
	}
	//绘制
	void Draw();

private:
	RECT_T m_tRect;
	unsigned short m_nRange; //不超过100
	unsigned short m_nPos;
};
//#endif