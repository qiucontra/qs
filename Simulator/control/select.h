//#ifndef _SELECT_H_
//#define _SELECT_H_
#pragma once
#include "../mmi/display.h"
#include "../option.h"

#define MAX_ITEM_NAME	24
#define SELECT_UP		0
#define SELECT_DOWN		1

typedef struct item_t
{
	unsigned int value;
	char name[MAX_ITEM_NAME+1];
}ITEM_T;

class MySelect
{
public:
	MySelect(unsigned int x, unsigned y, unsigned int width, unsigned height, FONT_SIZE font);
	MySelect(RECT_T rect, FONT_SIZE font);
	~MySelect();

public:
	//添加可以选择的项目
	void SetItem(unsigned int val, char * name);
	//选择项目
	int SelectItem(unsigned int opt);
	//获取当前项目的值
	unsigned int GetValue(){
		return m_pItem[m_nItemCur].value;
	}
	//获取当前项目的显示名称
	char * GetName(){
		return m_pItem[m_nItemCur].name;
	}
	unsigned int GetItemValue(unsigned int num){
		if (num < m_nItemCnt){
			return m_pItem[num].value;
		}
		return 0;
	}
	char * GetItemName(unsigned int num){
		if (num < m_nItemCnt){
			return m_pItem[num].name;
		}
		return NULL;
	}
	int SetDefault(unsigned int val){
		for (unsigned int i=0; i<m_nItemCnt; i++){
			if (m_pItem[i].value == val){
				m_nItemCur = i;
				return true;
			}
		}
		return false;
	}
	//移动控件的位置
	void Move(unsigned int x, unsigned int y){
		m_sRect.x = x;
		m_sRect.y = y;
	}
	RECT_T * GetRect(){
		return &m_sRect;
	};
	void Draw();
private:
	RECT_T m_sRect;
	ITEM_T * m_pItem;
	FONT_SIZE m_eFont;
	unsigned int m_nItemCnt;
	unsigned int m_nItemCur;
};

//#endif