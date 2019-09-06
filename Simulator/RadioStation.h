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
	//初始化
	void Init();
	//开机
	void PowerOn();
	//自检
	void SelfCheck();
	//处理主窗口
	void MainWindow();
	//关机
	void PowerOff();

public:
	//调节功率
	static int AdjustPower(void * pStation, unsigned int nKey);
	//调节音量
	static int AdjustVol(void * pStation, unsigned int nKey);
	//处理通道选择
	static int HandleSelectChannel(void * pStation, unsigned int nKey);
	//处理波形参数切换
	static int HandleSwitchWaveParam(void * pStation, unsigned int nKey);
	//处理返回窗口操作
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