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
	//��������ļ�����ֵ
	void SetLimit(unsigned int nLimit){
		m_nLimit = nLimit;
	};
	//��ȡ������ִ�
	char * GetValue(){
		return m_szValue;
	};
	//��ȡ�ؼ���rect
	RECT_T * GetRect(){
		return &m_tRect;
	}
	//����
	void InputChar(char ch);
	//����
	void Backspace();
	//����
	void Draw();

private:
	RECT_T m_tRect;
	unsigned int m_nLimit;
	unsigned int m_nNumCur;
	char m_szValue[INPUT_MAX+1];
	
	FONT_SIZE m_eFont;
};

//#endif