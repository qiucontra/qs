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
	CALLCHL_SATCOM = 0, //卫星通信
	CALLCHL_CHL1, //通道1
	CALLCHL_CHL2, //通道2
	CALLCHL_MAX
};
//处理输入电话号码
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
//处理选择通话的通道
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
//处理通话
int Call::HandleCalling(void * pStation, unsigned int nKey)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;

	Tooltip msg("通话中...");
	RECT_T * rect = msg.GetRect();
	msg.Show();
	dlg->Draw(rect->x, rect->y, rect->width, rect->height);
	Sleep(1000);
	msg.Resume();
	dlg->Draw(rect->x, rect->y, rect->width, rect->height);
	return 0;
}
//处理回退
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
//初始化拨号界面
int Call::Init(void * pStation, unsigned int nKey)
{
	RadioStation *station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndCall = new Wnd(WND_CALL);
	//添加号码输入控件，设置输入极限值为11
#if defined PIXEL_256X128
	MyInput * input = new MyInput(100, 48, FONT_MID);
#elif defined PIXEL_128X64
	MyInput * input = new MyInput(10, 22, FONT_MID);
#endif
	input->SetLimit(11);
	//添加三种通话通道
#if defined PIXEL_256X128
	MySelect * sel = new MySelect(100, 96, 60, 25, FONT_SMALL);
#elif defined PIXEL_128X64
	MySelect * sel = new MySelect(64, SCREEN_HEIGHT-20, 60, 20, FONT_SMALL);
#endif
	sel->SetItem(CALLCHL_SATCOM, "卫通");
	sel->SetItem(CALLCHL_CHL1, "CH1");
	sel->SetItem(CALLCHL_CHL2, "CH2");
	
	//设置父窗体
	wndCall->SetFather(station->m_pCurWnd);
	station->m_pCurWnd = wndCall;
	//为通话窗体添加控件
#ifdef PIXEL_256X128
	wndCall->AddControl(CTL_TITLEBAR, ID_WND_MAIN|ID_CTL_TITLEBAR, (void *)station->m_pTitleBar);
#endif
	wndCall->AddControl(CTL_INPUT, ID_WND_CALL|ID_CTL_CALL_NUMBER, (void *)input);
	wndCall->AddControl(CTL_SELECT, ID_WND_CALL|ID_CTL_CALL_CHL, (void *)sel);
	//为通话窗体添加监听
	wndCall->AddListener(KEY_ENTER, Call::HandleCalling);
	wndCall->AddListener(KEY_BACK, RadioStation::Back);
	wndCall->AddListener(KEY_UP, Call::HandleSelectCallChl);
	wndCall->AddListener(KEY_DOWN, Call::HandleSelectCallChl);
	//按Left键回退输入的号码
	wndCall->AddListener(KEY_LEFT, Call::HandleBackspace);
	for (int i=KEY_0; i<=KEY_9; i++){
		wndCall->AddListener(i, Call::HandleInputCallNumber);
	}

	Display::Clear();
	//不支持中文标点符号
#if defined PIXEL_256X128
	Display::PrintString("输入电话:", 10, 48, FONT_MID);
	Display::PrintString("通话方式:", 15, 96, FONT_SMALL);
#elif defined PIXEL_128X64
	Display::PrintString("输入电话:", 2, 5, FONT_SMALL);
	Display::PrintString("通话方式:", 2, SCREEN_HEIGHT-20, FONT_SMALL);
#endif
	wndCall->Layout();
	dlg->Draw();
	return 0;
}
