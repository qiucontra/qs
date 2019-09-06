//#ifndef _WAVESETTING_H_
//#define _WAVESETTING_H_
#pragma once
#include "../wave/wave.h"
#include "../control/paramset.h"
#include "../option.h"

class WaveSetting
{
public:
	//初始化波形设置界面
	static int Init(void * pStation, unsigned int nKey);
	//处理参数设置界面中上下选择参数
	static int HandleParamSelect(void * pStation, unsigned int nKey);
	//处理参数设置界面中按ENTER键，确认选择的参数
	static int HandleParamEnter(void * pStation, unsigned int nKey);
	//处理参数的更改，包括输入和选择
	static int HandleParamChange(void * pStation, unsigned int nKey);
	//处理参数回退操作
	static int ParamBack(void * pStation, unsigned int nKey);

public:
	//设置波形
	static ParamSet * SetWave(Wave * pWave);
	//处理选择类型的参数控件
	static int HandleParamSelectCtl(void * pParam, unsigned int nKey);
	//处理输入类型的参数控件
	static int HandleParamInputCtl(void * pParam, unsigned int nKey);
};

//#endif