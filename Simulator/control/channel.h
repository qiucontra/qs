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
	"通道1","通道2"
};

class Channel
{
public:
	Channel(unsigned int chl);
	~Channel();

public:
	Wave * m_pWave;

public:
	//切换波形参数
	void SwitchParam(unsigned int nKey);
	//设置通道
	//int ChannelSet(unsigned int nChl, unsigned type, unsigned int selected);
	//初始化波形的参数
	int InitWaveParam();
	int Draw();
	//获取通道号
	unsigned int GetChl(){
		return m_nChl;
	}
	//该通道是否被选中
	unsigned int isSelected(){
		return m_bSelected;
	};
	//将该通道设置为选中
	void SetSelected(bool bSelected){
		m_bSelected = bSelected;
	};

public:
	//获取通道的名称
	static char *GetChlName(unsigned int nChl){
		return ChlName[nChl];
	};
	//获取通道的中文名称
	static char *GetChlChsName(unsigned int nChl){
		return ChlChsName[nChl];
	};
	
private:
	//通道操作相关参数
	char m_szChl[4];
	unsigned int m_nChl;
	bool m_bSelected;
	MySelect * m_pParamCtl;
};

//#endif