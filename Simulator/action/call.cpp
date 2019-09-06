#include "stdafx.h"
#include "call.h"
#include "../mmi/display.h"
#include "../RadioStation.h"
#include "../SimulatorDlg.h"

#include "../control/input.h"
#include "../control/select.h"
#include "../control/tooltip.h"

#define ID_CTL_CALL_NUMBER		0
#define ID_CTL_CALL_CHL			1
#define ID_CTL_TITLEBAR			2

enum
{
	CALLCHL_SATCOM = 0, //����ͨ��
	CALLCHL_CHL1, //ͨ��1
	CALLCHL_CHL2, //ͨ��2
	CALLCHL_MAX
};
//��������绰����
int Call::HandleInputCallNumber(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;

	MyInput * input = (MyInput *)station->m_pCurWnd->GetItemById(ID_WND_CALL|ID_CTL_CALL_NUMBER);
	input->InputChar(nKey-KEY_0+0x30);

	RECT_T * rect = input->GetRect();
	dlg->Draw(rect->x, rect->y, rect->width, rect->height);
	return 0;
}
//����ѡ��ͨ����ͨ��
int Call::HandleSelectCallChl(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg * dlg = (CSimulatorDlg *)station->m_pDlg;

	MySelect * sel = (MySelect *)station->m_pCurWnd->GetItemById(ID_WND_CALL|ID_CTL_CALL_CHL);
	if (sel->SelectItem(nKey-KEY_UP) == true){
		RECT_T * rect = sel->GetRect();
		dlg->Draw(rect->x, rect->y, rect->width, rect->height);
	}
	return 0;
}
//����ͨ��
int Call::HandleCalling(void * pStation, unsigned int nKey)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;

	Tooltip msg("ͨ����...");
	RECT_T * rect = msg.GetRect();
	msg.Show();
	dlg->Draw(rect->x, rect->y, rect->width, rect->height);
	Sleep(1000);
	msg.Resume();
	dlg->Draw(rect->x, rect->y, rect->width, rect->height);
	return 0;
}
//�������
int Call::HandleBackspace(void * pStation, unsigned int nKey)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;

	MyInput * input = (MyInput *)station->m_pCurWnd->GetItemById(ID_WND_CALL|ID_CTL_CALL_NUMBER);
	input->Backspace();

	RECT_T * rect = input->GetRect();
	dlg->Draw(rect->x, rect->y, rect->width, rect->height);
	return 0;
}
//��ʼ�����Ž���
int Call::Init(void * pStation, unsigned int nKey)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndCall = new Wnd(WND_CALL);
	//��Ӻ�������ؼ����������뼫��ֵΪ11
#if defined PIXEL_256X128
	MyInput * input = new MyInput(100, 48, FONT_MID);
#elif defined PIXEL_128X64
	MyInput * input = new MyInput(10, 22, FONT_MID);
#endif
	input->SetLimit(11);
	//�������ͨ��ͨ��
#if defined PIXEL_256X128
	MySelect * sel = new MySelect(100, 96, 60, 25, FONT_SMALL);
#elif defined PIXEL_128X64
	MySelect * sel = new MySelect(64, SCREEN_HEIGHT-20, 60, 20, FONT_SMALL);
#endif
	sel->SetItem(CALLCHL_SATCOM, "��ͨ");
	sel->SetItem(CALLCHL_CHL1, "CH1");
	sel->SetItem(CALLCHL_CHL2, "CH2");
	
	//���ø�����
	wndCall->SetFather(station->m_pCurWnd);
	station->m_pCurWnd = wndCall;
	//Ϊͨ��������ӿؼ�
#ifdef PIXEL_256X128
	wndCall->AddControl(CTL_TITLEBAR, ID_WND_MAIN|ID_CTL_TITLEBAR, (void *)station->m_pTitleBar);
#endif
	wndCall->AddControl(CTL_INPUT, ID_WND_CALL|ID_CTL_CALL_NUMBER, (void *)input);
	wndCall->AddControl(CTL_SELECT, ID_WND_CALL|ID_CTL_CALL_CHL, (void *)sel);
	//Ϊͨ��������Ӽ���
	wndCall->AddListener(KEY_ENTER, Call::HandleCalling);
	wndCall->AddListener(KEY_BACK, RadioStation::Back);
	wndCall->AddListener(KEY_UP, Call::HandleSelectCallChl);
	wndCall->AddListener(KEY_DOWN, Call::HandleSelectCallChl);
	//��Left����������ĺ���
	wndCall->AddListener(KEY_LEFT, Call::HandleBackspace);
	for (int i=KEY_0; i<=KEY_9; i++){
		wndCall->AddListener(i, Call::HandleInputCallNumber);
	}

	Display::Clear();
	//��֧�����ı�����
#if defined PIXEL_256X128
	Display::PrintString("����绰:", 10, 48, FONT_MID);
	Display::PrintString("ͨ����ʽ:", 15, 96, FONT_SMALL);
#elif defined PIXEL_128X64
	Display::PrintString("����绰:", 2, 5, FONT_SMALL);
	Display::PrintString("ͨ����ʽ:", 2, SCREEN_HEIGHT-20, FONT_SMALL);
#endif
	wndCall->Layout();
	dlg->Draw();
	return 0;
}
