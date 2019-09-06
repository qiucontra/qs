//#ifndef _CHANNEL_H_
//#define _CHANNEL_H_
#pragma once
#include "../wave/wave.h"
#include "../option.h"
#include "paramset.h"
#include "select.h"

#define CHL_WIDTH			SCREEN_WIDTH
#define CHL_HEIGHT			CHANNEL_SIZE
#define CHL_SX				4
#define CHL_WAVENAME_SX		(4+38)
#define CHL_WAVENAME_SY		10
#define CHL_PARAM_SX		(4+38+68)
#define CHL_PARAM_SY		12
#define CHL_PARAM_HEIGHT	20

static char ChlName[CHL_MAX][16]={
	"CH1","CH2"
};

static char ChlChsName[CHL_MAX][16]={
	"ͨ��1","ͨ��2"
};

class Channel
{
public:
	Channel(unsigned int chl);
	~Channel();

public:
	Wave * m_pWave;

public:
	//�л����β���
	void SwitchParam(unsigned int nKey);
	//����ͨ��
	//int ChannelSet(unsigned int nChl, unsigned type, unsigned int selected);
	//��ʼ�����εĲ���
	int InitWaveParam();
	int Draw();
	//��ȡͨ����
	unsigned int GetChl(){
		return m_nChl;
	}
	//��ͨ���Ƿ�ѡ��
	unsigned int isSelected(){
		return m_bSelected;
	};
	//����ͨ������Ϊѡ��
	void SetSelected(bool bSelected){
		m_bSelected = bSelected;
	};

public:
	//��ȡͨ��������
	static char *GetChlName(unsigned int nChl){
		return ChlName[nChl];
	};
	//��ȡͨ������������
	static char *GetChlChsName(unsigned int nChl){
		return ChlChsName[nChl];
	};
	
private:
	//ͨ��������ز���
	char m_szChl[4];
	unsigned int m_nChl;
	bool m_bSelected;
	MySelect * m_pParamCtl;
};

//#endif