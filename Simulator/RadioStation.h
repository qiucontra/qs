//#ifndef _RADIOSTATION_H_
//#define _RADIOSTATION_H_
#pragma once
#include "./control/window.h"
#include "./control/channel.h"
#include "./control/optionbar.h"
#include "./control/titlebar.h"
#include "./action/protocol.h"

#define ID_WND_INIT			0x0000
#define ID_WND_SELFCHECK	0x0100
#define ID_WND_MAIN			0x0200
#define ID_WND_WAVESELECT	0x0300
#define ID_WND_WAVELOADING	0x0400
#define ID_WND_PARAMSET		0x0500
#define ID_WND_CALL			0x0600

class RadioStation
{
public:
	RadioStation(void * pDlg);
	~RadioStation();

public:
	//��ʼ��
	void Init();
	//����
	void PowerOn();
	//�Լ�
	void SelfCheck();
	//����������
	void MainWindow();
	//�ػ�
	void PowerOff();

public:
	//���ڹ���
	static int AdjustPower(void * pStation, unsigned int nKey);
	//��������
	static int AdjustVol(void * pStation, unsigned int nKey);
	//����ͨ��ѡ��
	static int HandleSelectChannel(void * pStation, unsigned int nKey);
	//�����β����л�
	static int HandleSwitchWaveParam(void * pStation, unsigned int nKey);
	//�����ش��ڲ���
	static int Back(void * pStation, unsigned int nKey);

public:
	Wnd * m_pMainWnd;
	Wnd * m_pCurWnd;
	void * m_pDlg;

	Channel * m_pChl[CHL_MAX];
	Channel * m_pCurChl;
	OptionBar * m_pOptionBar;
	TitleBar * m_pTitleBar;
};
//#endif