//#ifndef _WAVESETTING_H_
//#define _WAVESETTING_H_
#pragma once
#include "../wave/wave.h"
#include "../control/paramset.h"
#include "../option.h"

class WaveSetting
{
public:
	//��ʼ���������ý���
	static int Init(void * pStation, unsigned int nKey);
	//����������ý���������ѡ�����
	static int HandleParamSelect(void * pStation, unsigned int nKey);
	//����������ý����а�ENTER����ȷ��ѡ��Ĳ���
	static int HandleParamEnter(void * pStation, unsigned int nKey);
	//��������ĸ��ģ����������ѡ��
	static int HandleParamChange(void * pStation, unsigned int nKey);
	//����������˲���
	static int ParamBack(void * pStation, unsigned int nKey);

public:
	//���ò���
	static ParamSet * SetWave(Wave * pWave);
	//����ѡ�����͵Ĳ����ؼ�
	static int HandleParamSelectCtl(void * pParam, unsigned int nKey);
	//�����������͵Ĳ����ؼ�
	static int HandleParamInputCtl(void * pParam, unsigned int nKey);
};

//#endif