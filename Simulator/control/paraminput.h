//#ifndef _PARAMINPUT_H_
//#define _PARAMINPUT_H_
#pragma once
#include "../wave/wave.h"
#include "../option.h"
#include "../mmi/display.h"

#define PARAM_INPUT_MAX		24

enum
{
	PARAMINPUT_FREQ = 0,
	PARAMINPUT_IP,
	PARAMINPUT_PORT,
	PARAMINPUT_MAC,
	PARAMINPUT_NETID,
	PARAMINPUT_NETSIZE,
	PARAMINPUT_RTRES,
	PARAMINPUT_MAX
};

class ParamInput
{
public:
	ParamInput(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, FONT_SIZE eFont);
	ParamInput(RECT_T tRect, FONT_SIZE rFont);
	~ParamInput();

public:
	int HandleFreq(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleMac(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleLocalPort(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleLocalIp(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleRemotePort(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleRemoteIp(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleNetId(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleNetSize(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	int HandleRtResource(Wave * pWave, unsigned int bSelected, unsigned int nKey);
	void SetInputType(unsigned int nInputType){
		m_nInputType = nInputType;
	}
	char * GetValue(){
		return m_szValue;
	}
	void SetValue(char * val){
		STRCPY(m_szValue, val);
	}
	void Draw();
	//移动控件的位置
	void Move(unsigned int nX, unsigned int nY){
		m_tRect.x = nX;
		m_tRect.y = nY;
	}
	int isShift(){
		return m_bShift;
	};
private:
	RECT_T m_tRect;
	FONT_SIZE m_eFont;
	unsigned int m_nInputType;
	unsigned int m_nInputNum;
	unsigned int m_nOrder;
	int m_nValue;
	bool m_bShift;
	char m_szValue[PARAM_INPUT_MAX+1];
};


//#endif