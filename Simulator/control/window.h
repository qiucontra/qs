//#ifndef _WINDOW_H_
//#define _WINDOW_H_
#pragma once
#include "../wave/wave.h"
#include "../option.h"

typedef struct control_t
{
	unsigned int id;
	CTL_TYPE type;
	void * item;
}CONTROL_T;

typedef struct listener_t
{
	unsigned int keynum;
	int (* callback)(void *, unsigned int);
}LISTENER_T;

class Wnd
{
public:
	Wnd(WND_TYPE nType);
	~Wnd();

public:
	//给窗体添加一个控件
	int AddControl(CTL_TYPE nCtlType, unsigned int nId, void * pItem);
	//清楚窗体所有的控件
	void ClearControl();
	//给窗体添加一个监听
	int AddListener(unsigned int nLisType, int (* cb)(void *, unsigned int));
	//通过ID获取控件
	void * GetItemById(unsigned int nId);
	//窗体布局
	void Layout();
	//消息处理的统一Handle函数
	int Handle(void * pObj, unsigned int nType);
	//获取父窗口
	Wnd * GetFather(){
		return m_pFather;
	}
	//涉资父窗口
	void SetFather(Wnd * pFather){
		m_pFather = pFather;
	}

private:
	Wnd * m_pFather;
	WND_TYPE m_nType;
	CONTROL_T * m_pCtlLst;
	CONTROL_T * m_pCtlStart;
	CONTROL_T * m_pCtlEnd;
	LISTENER_T m_tListener[KEY_MAX];
	unsigned int m_nCtlNum;
};
//#endif