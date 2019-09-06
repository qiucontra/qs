#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "select.h"
#include "../option.h"

MySelect::MySelect(unsigned int x, unsigned y, unsigned int width, unsigned height, FONT_SIZE font)
{
	m_sRect.x = x;
	m_sRect.y = y;
	m_sRect.width = width;
	m_sRect.height = height;
	m_nItemCur = 0;
	m_nItemCnt = 0;
	m_eFont = font;
	m_pItem = NULL;
}

MySelect::MySelect(RECT_T rect, FONT_SIZE font)
{
	MySelect(rect.x, rect.y, rect.width, rect.height, font);
}

MySelect::~MySelect()
{
	free(m_pItem);
	m_nItemCnt = m_nItemCur = 0;
}

void MySelect::SetItem(unsigned int val, char * name)
{
	ITEM_T * tmp = (ITEM_T *)calloc(m_nItemCnt+1, sizeof(ITEM_T));
	ITEM_T * cur = &tmp[m_nItemCnt];
	//如果之前的指针不为空，表示原先已有Item，将原有Item复制
	if (m_pItem != NULL){
		memcpy(tmp, m_pItem, sizeof(ITEM_T)*m_nItemCnt); 
		free(m_pItem);
	}

	cur->value = val;
	memcpy(cur->name, name, sizeof(char)*strlen(name));
	m_pItem = tmp;
	m_nItemCnt ++;
}

int MySelect::SelectItem(unsigned int opt)
{
	int nRst = false;
	if (opt == SELECT_UP){
		if (m_nItemCur > 0){
			m_nItemCur --;
			nRst = true;
		}
	}
	else if (opt == SELECT_DOWN){
		if (m_nItemCur < (m_nItemCnt-1)){
			m_nItemCur ++;
			nRst = true;
		}
	}
	else {
		printf("[%s]param error<%d>\n", __FUNCTION__, opt);
		return false;
	}

	if (nRst == true){
		Draw();
	}
	return nRst;
}

void MySelect::Draw()
{
	Display::Clear(m_sRect.x, m_sRect.y, m_sRect.width, m_sRect.height);
	Display::PrintString(m_pItem[m_nItemCur].name, m_sRect.x, m_sRect.y, m_eFont);
}