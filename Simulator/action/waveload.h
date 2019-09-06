//#ifndef _WAVELOAD_H_
//#define _WAVELOAD_H_
#pragma once

class WaveLoad
{
public:
	//初始化波形加载窗体
	static int Init(void * pStation, unsigned int nKey);
	//处理波形选择
	static int HandleSelect(void * pStation, unsigned int nKey);
	//处理波形加载
	static int HandleLoad(void * pStation, unsigned int nKey);
	//波形加载
	static int LoadWave(void * pStation, unsigned int nWaveType);
	//波形卸载
	static int UnloadWave(void * pStation, unsigned int nWaveType);
};

//#endif