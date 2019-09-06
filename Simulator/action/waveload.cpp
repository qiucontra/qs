#include "stdafx.h"
#include "waveload.h"
#include "../RadioStation.h"
#include "../SimulatorDlg.h"

#include "../option.h"
#include "../control/window.h"
#include "../control/process.h"
#include "../control/waveselect.h"
#include "../action/waveload.h"


#define ID_CTL_TITLEBAR		0
#define ID_CTL_OPTIONBAR	1
#define ID_CTL_WAVESELECT	2
//WaveLoad ���μ��ز���===========================================//
//===================================================================//
//���μ���
int WaveLoad::LoadWave(void * pStation, unsigned int nWaveType)
{
	char buffer[64];
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;

	SPRINTF(buffer, "%s���μ�����...\0", Wave::GetWaveName(nWaveType));
	Display::Clear();
#if defined PIXEL_256X128
	Display::PrintString(Channel::GetChlChsName(station->m_pCurChl->GetChl()), 16, 24, FONT_SMALL);
	Display::PrintString(buffer, 48, 56, FONT_SMALL);

	MyProcess * process = new MyProcess(20, 128-40, 256-40, 20, 100);
#elif defined PIXEL_128X64
	Display::PrintString(Channel::GetChlChsName(station->m_pCurChl->GetChl()), 4, 6, FONT_SMALL);
	Display::PrintString(buffer, 20, 24, FONT_SMALL);

	MyProcess * process = new MyProcess(5, SCREEN_HEIGHT-20, SCREEN_WIDTH-10, 10, 100);
#endif
	for (int i=0; i<=10; i++){
		process->SetPos(10*i);
		dlg->Draw();
		Sleep(10);
	}
	DELETE_OBJ(process);

	//���سɹ����½�����
	if (station->m_pCurChl->m_pWave != NULL){
		delete station->m_pCurChl->m_pWave;
	}

	station->m_pCurChl->m_pWave = new Wave(nWaveType, station->m_pCurChl->GetChl());
	//update config file

	station->m_pCurChl->InitWaveParam();
	RadioStation::Back(pStation, KEY_BACK);
	return true;
}
//����ж��
int WaveLoad::UnloadWave(void * pStation, unsigned int nWaveType)
{
	char buffer[64];
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;

	SPRINTF(buffer, "%s����ж����...\0", Wave::GetWaveName(nWaveType));
	Display::Clear();
#if defined PIXEL_256X128
	Display::PrintString(Channel::GetChlChsName(station->m_pCurChl->GetChl()), 16, 24, FONT_SMALL);
	Display::PrintString(buffer, 48, 56, FONT_SMALL);

	MyProcess * process = new MyProcess(20, 128-40, 256-40, 20, 100);
#elif defined PIXEL_128X64
	Display::PrintString(Channel::GetChlChsName(station->m_pCurChl->GetChl()), 4, 6, FONT_SMALL);
	Display::PrintString(buffer, 20, 24, FONT_SMALL);

	MyProcess * process = new MyProcess(5, SCREEN_HEIGHT-20, SCREEN_WIDTH-10, 10, 100);
#endif
	for (int i=0; i<=10; i++){
		process->SetPos(10*i);
		dlg->Draw();
		Sleep(10);
	}
	DELETE_OBJ(process);

	if (station->m_pCurChl->m_pWave != NULL){
		delete station->m_pCurChl->m_pWave;
		station->m_pCurChl->m_pWave = NULL;
	}
	RadioStation::Back(pStation, KEY_BACK);
	return true;
}
//�����μ���
int WaveLoad::HandleLoad(void * pStation, unsigned int key)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;
	//ȷ��ѡ��Ĳ�����Ϣ
	WaveSelect * wavesel = (WaveSelect *)station->m_pCurWnd->GetItemById(ID_WND_WAVESELECT|ID_CTL_WAVESELECT);
	WAVESELECT_T * wave = wavesel->GetCurWave();

	//����ж�صĲ���
	if (wave->type == WAVE_UNLOAD){
		WaveLoad::UnloadWave(pStation, wave->type);
	}
	else {
		WaveLoad::LoadWave(pStation, wave->type);
	}

	return true;
}
//������ѡ��
int WaveLoad::HandleSelect(void * pStation, unsigned int key)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndSelectWave = station->m_pCurWnd;
	WaveSelect *sel = (WaveSelect *)wndSelectWave->GetItemById(ID_WND_WAVESELECT|ID_CTL_WAVESELECT);

	sel->Switch(key);
	sel->Draw();
	dlg->Draw();
	return true;
}
//��ʼ�����μ��ش���
int WaveLoad::Init(void * pStation, unsigned int key)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndWaveLoad = new Wnd(WND_WAVESELECT);
	WaveSelect *sel = new WaveSelect(station->m_pCurChl->GetChl());

	//���ø�����
	wndWaveLoad->SetFather(station->m_pCurWnd);
	//Ϊ���μ��ش�����ӿؼ�
#if defined PIXEL_256X128
	wndWaveLoad->AddControl(CTL_OPTIONBAR, ID_WND_WAVESELECT|ID_CTL_OPTIONBAR, (void *)station->m_pOptionBar);
	wndWaveLoad->AddControl(CTL_TITLEBAR, ID_WND_WAVESELECT|ID_CTL_TITLEBAR, (void *)station->m_pTitleBar);
#endif
	wndWaveLoad->AddControl(CTL_WAVESELECT, ID_WND_WAVESELECT|ID_CTL_WAVESELECT, (void *)sel);
	//��Ӱ�������
#if defined PIXEL_256X128
	wndWaveLoad->AddListener(KEY_2, RadioStation::AdjustPower);
	wndWaveLoad->AddListener(KEY_7, RadioStation::AdjustPower);
	wndWaveLoad->AddListener(KEY_4, RadioStation::AdjustVol);
	wndWaveLoad->AddListener(KEY_9, RadioStation::AdjustVol);
#endif
	wndWaveLoad->AddListener(KEY_UP, WaveLoad::HandleSelect);
	wndWaveLoad->AddListener(KEY_DOWN, WaveLoad::HandleSelect);
	wndWaveLoad->AddListener(KEY_LEFT, WaveLoad::HandleSelect);
	wndWaveLoad->AddListener(KEY_RIGHT, WaveLoad::HandleSelect);
	wndWaveLoad->AddListener(KEY_BACK, RadioStation::Back);
	wndWaveLoad->AddListener(KEY_ENTER, WaveLoad::HandleLoad);

	//���õ�ǰ����
	station->m_pCurWnd = wndWaveLoad;
	Display::Clear();
	wndWaveLoad->Layout();
	dlg->Draw();
	return true;
}