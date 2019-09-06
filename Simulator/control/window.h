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
	//���������һ���ؼ�
	int AddControl(CTL_TYPE nCtlType, unsigned int nId, void * pItem);
	//����������еĿؼ�
	void ClearControl();
	//���������һ������
	int AddListener(unsigned int nLisType, int (* cb)(void *, unsigned int));
	//ͨ��ID��ȡ�ؼ�
	void * GetItemById(unsigned int nId);
	//���岼��
	void Layout();
	//��Ϣ�����ͳһHandle����
	int Handle(void * pObj, unsigned int nType);
	//��ȡ������
	Wnd * GetFather(){
		return m_pFather;
	}
	//���ʸ�����
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