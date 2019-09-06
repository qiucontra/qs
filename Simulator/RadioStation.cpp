#include "stdafx.h"
#include "RadioStation.h"
#include "SimulatorDlg.h"
#include "option.h"

#include "./control/paramset.h"
#include "./control/process.h"
#include "./control/tooltip.h"

#include "./action/waveload.h"
#include "./action/wavesetting.h"
#include "./action/selfcheck.h"
#include "./action/call.h"

#define ID_CTL_TITLEBAR		0x0000
#define ID_CTL_OPTIONBAR	0x0001
#define ID_CTL_CHL1			0x0002
#define ID_CTL_CHL2			0x0003
//RadioStation ======================================================//
//===================================================================//
//���ڵ��ڹ���
RadioStation::RadioStation(void * pDlg)
{
	m_pMainWnd = NULL;
	m_pCurWnd = NULL;
	m_pDlg = pDlg;
	m_pOptionBar = NULL;
	m_pTitleBar = NULL;
	m_pChl[CHL_1] = NULL;
	m_pChl[CHL_2] = NULL;
}

RadioStation::~RadioStation()
{
	//�����ǰ������������Ļ���ֻ��Ҫɾ��������
	if (m_pCurWnd == m_pMainWnd){
		DELETE_OBJ(m_pMainWnd);
	}
	else {
		DELETE_OBJ(m_pMainWnd);
		DELETE_OBJ(m_pCurWnd);
	}	
}

//���ز���
int RadioStation::Back(void * p, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)p;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndFather = station->m_pCurWnd->GetFather();

	DELETE_OBJ(station->m_pCurWnd);
	station->m_pCurWnd = wndFather;
	Display::Clear();
	station->m_pCurWnd->Layout();

	dlg->Draw();
	return 0;
}
//���ڹ���
int RadioStation::AdjustPower(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;
	OptionBar *optionBar = (OptionBar *)station->m_pCurWnd->GetItemById(ID_WND_MAIN|ID_CTL_OPTIONBAR);
	if (optionBar != NULL){
		optionBar->Control(OPTION_CTL_PWR, nKey);
	}

	dlg->Draw(OPTIONBAR_AREA_X, OPTIONBAR_AREA_Y, OPTIONBAR_AREA_W, OPTIONBAR_AREA_H);
	return 0;
}
//���ڵ�������
int RadioStation::AdjustVol(void * pStation, unsigned int nKey)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	OptionBar *optionBar = (OptionBar *)station->m_pCurWnd->GetItemById(ID_WND_MAIN|ID_CTL_OPTIONBAR);
	if (optionBar != NULL){
		optionBar->Control(OPTION_CTL_VOL, nKey);
	}

	dlg->Draw(OPTIONBAR_AREA_X, OPTIONBAR_AREA_Y, OPTIONBAR_AREA_W, OPTIONBAR_AREA_H);
	return 0;
}

int RadioStation::HandleSelectChannel(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;

	if (station->m_pCurChl == station->m_pChl[CHL_1]){
		station->m_pCurChl->SetSelected(false);
		station->m_pChl[CHL_2]->SetSelected(true);
		station->m_pCurChl = station->m_pChl[CHL_2];
	}
	else {
		station->m_pCurChl->SetSelected(false);
		station->m_pChl[CHL_1]->SetSelected(true);
		station->m_pCurChl = station->m_pChl[CHL_1];
	}

	station->m_pChl[CHL_1]->Draw();
	station->m_pChl[CHL_2]->Draw();
	dlg->Draw(CHANNEL_AREA_X, CHANNEL_AREA_Y, CHANNEL_AREA_W, CHANNEL_AREA_H);
	return 0;
}

int RadioStation::HandleSwitchWaveParam(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;

	if (station->m_pCurChl->m_pWave != NULL){
		station->m_pCurChl->SwitchParam(nKey);
		station->m_pCurChl->Draw();

		CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
		dlg->Draw();
	}
	return 0;
}

void RadioStation::PowerOn()
{
	Wnd * wndInit = new Wnd(WND_INIT);
	CSimulatorDlg *dlg = (CSimulatorDlg *)m_pDlg;
#if defined PIXEL_256X128
	Display::PrintString("�й����ӿƼ����ŵ���ʮ�о���", 8, 24, FONT_SMALL);
	Display::PrintString("������ߵ�̨", 64, 56, FONT_MID);

	MyProcess * process = new MyProcess(20, SCREEN_HEIGHT-40, SCREEN_WIDTH-40, 20, 100);
#elif defined PIXEL_128X64
	Display::PrintString("�й���Ƶ���ʮ�о���", 2, 8, FONT_SMALL);
	Display::PrintString("������ߵ�̨", 12, 24, FONT_MID);
	
	MyProcess * process = new MyProcess(5, SCREEN_HEIGHT-20, SCREEN_WIDTH-10, 10, 100);
#endif
	for (int i=0; i<=10; i++){
		process->SetPos(10*i);
		dlg->Draw();
		Sleep(10);
	}
	DELETE_OBJ(process);
	delete wndInit;
}

void RadioStation::SelfCheck()
{
	SelfCheck::Init((void *)this);
}

void RadioStation::MainWindow()
{
	CSimulatorDlg * dlg = (CSimulatorDlg *)m_pDlg;
	m_pMainWnd = new Wnd(WND_MAIN);

	//������������������������ͨ��
	m_pOptionBar = new OptionBar(PWR_MID, 0, VOL_1);
	m_pTitleBar = new TitleBar();
	m_pChl[CHL_1] = new Channel(CHL_1);
	m_pChl[CHL_2] = new Channel(CHL_2);
	//��ǰͨ������ΪCHL1
	m_pCurChl = m_pChl[CHL_1];
	m_pCurChl->SetSelected(true);
	//Ϊ��������ӿؼ�
	m_pMainWnd->AddControl(CTL_OPTIONBAR, ID_WND_MAIN|ID_CTL_OPTIONBAR, (void *)m_pOptionBar);
	m_pMainWnd->AddControl(CTL_TITLEBAR, ID_WND_MAIN|ID_CTL_TITLEBAR, (void *)m_pTitleBar);
	m_pMainWnd->AddControl(CTL_CHANNEL, ID_WND_MAIN|ID_CTL_CHL1, (void *)m_pChl[CHL_1]);
	m_pMainWnd->AddControl(CTL_CHANNEL, ID_WND_MAIN|ID_CTL_CHL2, (void *)m_pChl[CHL_2]);
	//Ϊ��������Ӱ�������
	m_pMainWnd->AddListener(KEY_2, RadioStation::AdjustPower);
	m_pMainWnd->AddListener(KEY_7, RadioStation::AdjustPower);
	m_pMainWnd->AddListener(KEY_4, RadioStation::AdjustVol);
	m_pMainWnd->AddListener(KEY_9, RadioStation::AdjustVol);
	m_pMainWnd->AddListener(KEY_UP, RadioStation::HandleSelectChannel);
	m_pMainWnd->AddListener(KEY_DOWN, RadioStation::HandleSelectChannel);
	m_pMainWnd->AddListener(KEY_LEFT, RadioStation::HandleSwitchWaveParam);
	m_pMainWnd->AddListener(KEY_RIGHT, RadioStation::HandleSwitchWaveParam);
	//���MENU���ز���
	m_pMainWnd->AddListener(KEY_5, WaveLoad::Init);
	//���SET���ò��β���
	m_pMainWnd->AddListener(KEY_0, WaveSetting::Init);
	//���call�����绰����
	m_pMainWnd->AddListener(KEY_1, Call::Init);
	//���õ�ǰ����Ϊm_pMainWnd
	m_pCurWnd = m_pMainWnd;

	//��ʱ�޸�
	//m_pCurChl->m_pWave = new Wave(1, 1);
	//m_pCurChl->m_pWave = new Wave(1, 1);
	//update config file
	//m_pCurChl->InitWaveParam();

	//����������
	Display::Clear();
	m_pMainWnd->Layout();
	dlg->Draw();
}
//===================================================================//

