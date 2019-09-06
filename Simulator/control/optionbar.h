//#ifndef _OPTIONBAR_H_
//#define _OPTIONBAR_H_
#pragma once
#include "../mmi/display.h"
#include "../option.h"
#include "select.h"

#define OPTIONBAR_SY	(SCREEN_HEIGHT - OPTIONBAR_SIZE)
#if defined PIXEL_256X128
#define OPTIONBAR_SIZE	24
#define OPTION_PWR_SX	(0+4)
#define OPTION_CHL_SX	(85+16)
#define OPTION_VOL_SX	(85*2+24)
#elif defined PIXEL_128X64
#define OPTIONBAR_SIZE	16
#define OPTION_PWR_SX	(0+2)
#define OPTION_CHL_SX	(40+8)
#define OPTION_VOL_SX	(40*2+10)
#endif

typedef enum
{
	OPTION_CTL_PWR = 0,
	OPTION_CTL_CHL,
	OPTION_CTL_VOL
}OPTION_CTL;

enum 
{
	PWR_SMALL = 0,
	PWR_MID,
	PWR_LARGE,
	PWR_MAX
};

typedef enum
{
	VOL_0 = 0,
	VOL_1,
	VOL_2,
	VOL_3,
	VOL_MAX
};

class OptionBar
{
public:
	OptionBar(unsigned int nPwr, unsigned int nChl, unsigned int nVol);
	~OptionBar();

public:
	//功能条中的音量，功率等控制接口
	void Control(OPTION_CTL eCtlType, unsigned int nKey);
	void Draw();

private:
	MySelect * m_pPwr;
	MySelect * m_pChl;
	MySelect * m_pVol;
};

//#endif