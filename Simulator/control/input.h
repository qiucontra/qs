//#ifndef _INPUT_H_
//#define _INPUT_H_
#pragma once
#include "../mmi/display.h"
#include "../mmi//zimo.h"
#include "../option.h"

#define INPUT_MAX	16

class MyInput
{
public:
	MyInput(unsigned int nX, unsigned int nY, FONT_SIZE eFont);
	~MyInput();

public:
	//设置输入的极限数值
	void SetLimit(unsigned int nLimit){
		m_nLimit = nLimit;
	};
	//获取输入的字串
	char * GetValue(){
		return m_szValue;
	};
	//获取控件的rect
	RECT_T * GetRect(){
		return &m_tRect;
	}
	//输入
	void InputChar(char ch);
	//回退
	void Backspace();
	//绘制
	void Draw();

private:
	RECT_T m_tRect;
	unsigned int m_nLimit;
	unsigned int m_nNumCur;
	char m_szValue[INPUT_MAX+1];
	
	FONT_SIZE m_eFont;
};

//#endif