//#ifndef _PARAM_SET_
//#define _PARAM_SET_
#pragma once
#include "../mmi/display.h"
#include "../wave/wave.h"

#include "select.h"

#if defined PIXEL_256X128
#define MAX_PARAM_CNT_ONEPAGE	6
#elif defined PIXEL_128X64
#define MAX_PARAM_CNT_ONEPAGE	4
#endif

enum
{
	PARAM_MODE_SELECT = 0, //通过上下选择参数
	PARAM_MODE_INPUT, //通过输入填写参数
	PARAM_MODE_MAX
};

typedef struct param_t
{
	unsigned int num;
	unsigned int type;
	unsigned int mode; //参数的输入模式，"PARAM_MODE_SELECT、PARAM_MODE_INPUT"
	bool visible;
	char name[WAVE_PARAM_MAX];
	void * control; //对应的控件
	int (* ctl)(void *, unsigned int);
}PARAM_T;

class ParamSet
{
public:
	ParamSet(Wave * pWave);
	~ParamSet();
	
public:
	int Switch(unsigned int nKey);
	void Draw(void);

	int AddParam(unsigned int nParamType, unsigned int nInputMode, int (* ctl)(void *, unsigned int)=NULL);
	int AddParamSelectItem(unsigned int nNumber, unsigned int nValue, char * pszName);
	int SetParamValue(unsigned int nNumber, unsigned int nValue);
	int SetInput(unsigned int nNumber, unsigned int nInputType, char * pValue);
	int SetParamStartEnd(unsigned int nNumberStart, unsigned int nNumberEnd);
	int SetVisible(unsigned int nNumber, bool bVisible);
	Wave * GetWave(){
		return m_pWave;
	}
	PARAM_T * GetCurParam(){
		return m_pParamCur;
	};
	bool isSelected(){
		return m_bSelected;
	}
	void SetSelected(bool bSelected){
		m_bSelected = bSelected;
	}
	unsigned int GetNum(unsigned int nParamType){
		if (nParamType < PARAM_MAX){
			for (unsigned int i=0; i<m_nParamCnt; i++){
				if (m_pParam[i].type == nParamType){
					return m_pParam[i].num;
				}
			}
		}
		return 0xff;
	};

private:
	Wave * m_pWave;
	unsigned int m_nX;
	unsigned int m_nY;

	PARAM_T * m_pParam;
	PARAM_T * m_pParamStart;
	PARAM_T * m_pParamEnd;
	PARAM_T * m_pParamCur;
	unsigned int m_nParamCnt;
	bool m_bAutoScroll;
	bool m_bSelected;

	void * AddControl(unsigned int mode);
};



//#endif