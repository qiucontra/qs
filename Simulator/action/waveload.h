//#ifndef _WAVELOAD_H_
//#define _WAVELOAD_H_
#pragma once

class WaveLoad
{
public:
	//��ʼ�����μ��ش���
	static int Init(void * pStation, unsigned int nKey);
	//������ѡ��
	static int HandleSelect(void * pStation, unsigned int nKey);
	//�����μ���
	static int HandleLoad(void * pStation, unsigned int nKey);
	//���μ���
	static int LoadWave(void * pStation, unsigned int nWaveType);
	//����ж��
	static int UnloadWave(void * pStation, unsigned int nWaveType);
};

//#endif