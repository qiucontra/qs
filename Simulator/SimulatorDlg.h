
// SimulatorDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"
#include "./mmi/display.h"
#include "RadioStation.h"

// CSimulatorDlg �Ի���
class CSimulatorDlg : public CDialogEx
{
// ����
public:
	CSimulatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIMULATOR_DIALOG };

public:
	void Draw(int sx=0, int sy=0, int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
	unsigned int m_rssi;
	unsigned int m_battery;
	unsigned int m_hour;
	unsigned int m_minute;

	//tm = CTime::GetCurrentTime();

	//void CSimulatorDlg::DrawRectangle(int x,int y,int l, int h);
	void Layout();
	
	char m_ch;
	//add by qiushi 2018-09-23
	RadioStation * m_pRadio;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonPower();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButtonMenu();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnClose();
};
