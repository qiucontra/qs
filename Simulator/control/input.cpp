#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

MyInput::MyInput(unsigned int nX, unsigned int nY, FONT_SIZE eFont)
{
	m_tRect.x = nX;
	m_tRect.y = nY;
	m_eFont = eFont;
	m_nLimit = 0;
	m_nNumCur = 0;
	m_nLimit = INPUT_MAX;
	memset(m_szValue, 0, sizeof(char)*(INPUT_MAX+1));
}

MyInput::~MyInput()
{

}

void MyInput::InputChar(char ch)
{
	//在极限值能准许输入
	if (strlen(m_szValue) < m_nLimit){
		m_szValue[m_nNumCur++] = ch;
		Draw();
	}
};

void MyInput::Backspace()
{
	if (m_nNumCur > 0){
		m_szValue[m_nNumCur-1] = '\0';
		m_nNumCur --;
		Draw();
	}
}

void MyInput::Draw()
{
	int width=0,height=0;

	Zimo::GetAscSize(m_eFont, &width, &height);
	m_tRect.width = strlen(m_szValue) * width + 1;
	m_tRect.height = height+1;

	//首先需要按照极限输入进行清屏，否则无法完成回退功能
	Display::Clear(m_tRect.x, m_tRect.y, m_nLimit*width+1, m_tRect.height);
	Display::PrintString(m_szValue, m_tRect.x, m_tRect.y, m_eFont);
}