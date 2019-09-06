
// SimulatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Simulator.h"
#include "SimulatorDlg.h"
#include "afxdialogex.h"

#include "option.h"

#include "RadioStation.h"
#include "./control/window.h"
#include "./control/channel.h"
#include "./control/optionbar.h"
#include "./control/titlebar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSimulatorDlg �Ի���
#define SREEN_SX		10
#define SREEN_SY		20

CSimulatorDlg::CSimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimulatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_0, &CSimulatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CSimulatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CSimulatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CSimulatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CSimulatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CSimulatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CSimulatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CSimulatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CSimulatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CSimulatorDlg::OnBnClickedButton9)	
	ON_BN_CLICKED(IDC_BUTTON_UP, &CSimulatorDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CSimulatorDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_POWER, &CSimulatorDlg::OnBnClickedButtonPower)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CSimulatorDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CSimulatorDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_MENU, &CSimulatorDlg::OnBnClickedButtonMenu)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CSimulatorDlg::OnBnClickedButtonBack)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSimulatorDlg ��Ϣ�������

BOOL CSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	Layout();
	//DisplayInit();
	//DisplayImage(16,0,14,14,SYSMINRELEASE);
	//DisplayImage(256-40, 4, 29, 16, battery);

	//char aa[] = "��";

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}



// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		//DrawRectangle(SREEN_SX, SREEN_SY, 256*2, 128*2);
		Draw();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSimulatorDlg::Layout()
{
	CRect rc;
	unsigned int w = 95;
	unsigned int h = 40;
#define SCREEN_W	256
#define SCREEN_H	128

	CRect rcMain;
	this->GetWindowRect(&rcMain);
	rcMain.right = rcMain.left + 840;
	rcMain.bottom = rcMain.top + 480;
	this->MoveWindow(rcMain);

	//��Ļ
	rc.left = SREEN_SX;
	rc.top = SREEN_SY;
	rc.right = SREEN_SX + SCREEN_W*2;
	rc.bottom = SREEN_SY + SCREEN_H*2;
	GetDlgItem(IDC_STATIC_SCREEN)->MoveWindow(rc);

	//�²�����
	rc.top = rc.bottom + 20;
	rc.right = rc.left + w;
	rc.bottom = rc.top + h;
	GetDlgItem(IDC_BUTTON_1)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_2)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_3)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_4)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_5)->MoveWindow(rc);

	rc.left = SREEN_SX;
	rc.top = rc.bottom + 15;
	rc.right = rc.left + w;
	rc.bottom = rc.top + h;
	GetDlgItem(IDC_BUTTON_6)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_7)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_8)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_9)->MoveWindow(rc);

	rc.left = rc.right+10;
	rc.right = rc.left + w;
	GetDlgItem(IDC_BUTTON_0)->MoveWindow(rc);

	//�Ҳఴť
	rc.left = SREEN_SX + SCREEN_W*2 + 70;
	rc.top = SREEN_SY;
	rc.right = rc.left + 150;
	rc.bottom = rc.top + 50;
	GetDlgItem(IDC_BUTTON_POWER)->MoveWindow(rc);

	rc.top = rc.bottom + 20;
	rc.bottom = rc.top + 50;
	GetDlgItem(IDC_BUTTON_MENU)->MoveWindow(rc);

	rc.top = rc.bottom + 20;
	rc.bottom = rc.top + 50;
	GetDlgItem(IDC_BUTTON_BACK)->MoveWindow(rc);

	//�����
	rc.left = SREEN_SX + SCREEN_W*2 + 110;
	rc.top = rc.bottom + 30;
	rc.right = rc.left + 75;
	rc.bottom = rc.top + 50;
	GetDlgItem(IDC_BUTTON_UP)->MoveWindow(rc);

	rc.top = rc.bottom + 20;
	rc.bottom = rc.top + 50;
	GetDlgItem(IDC_BUTTON_DOWN)->MoveWindow(rc);

	rc.left = rc.left - 75 - 15;
	rc.top = rc.top - 35;
	rc.right = rc.left + 75;
	rc.bottom = rc.top + 50;
	GetDlgItem(IDC_BUTTON_LEFT)->MoveWindow(rc);

	rc.left = rc.right + 75 + 30;
	rc.right = rc.left + 75;
	GetDlgItem(IDC_BUTTON_RIGHT)->MoveWindow(rc);
}

void CSimulatorDlg::Draw(int sx, int sy, int width, int height)
{
	CDC* pControlDC=GetDlgItem(IDC_STATIC_SCREEN)->GetDC();

	CDC MemDC; //���ȶ���һ����ʾ�豸����
	CBitmap MemBitmap;//����һ��λͼ����

	#define COLOR_DISPLAY		RGB(0, 0, 0)
	#define COLOR_UNDISPLAY		RGB(0xFF, 0xFF, 0xFF)

	int nWidth = SCREEN_WIDTH*2;
	int nHeight = SCREEN_HEIGHT*2;
	int x=0,y=0;
	unsigned char *buffer = Display::GetScreen();

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemDC.CreateCompatibleDC(NULL);
	//��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С
	MemBitmap.CreateCompatibleBitmap(pControlDC, nWidth, nHeight);

	//��λͼѡ�뵽�ڴ���ʾ�豸��
	//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	//���ñ���ɫ��λͼ����ɾ�
	//��Ҳ�������Լ�Ӧ���õ���ɫ
	COLORREF color = (COLORREF)(0,0,0);//(COLORREF) GetSysColor(COLOR_BTNFACE);
	MemDC.FillSolidRect(0, 0, nWidth, nHeight, color);

	for (x=0; x<SCREEN_WIDTH; x++){
		for (y=0; y<SCREEN_HEIGHT; y++){
			if (buffer[SCREEN_WIDTH*y+x] == 0){
				MemDC.SetPixel(2*x,2*y,COLOR_UNDISPLAY);
				MemDC.SetPixel(2*x+1,2*y,COLOR_UNDISPLAY);
				MemDC.SetPixel(2*x,2*y+1,COLOR_UNDISPLAY);
				MemDC.SetPixel(2*x+1,2*y+1,COLOR_UNDISPLAY);
			}
			else{
				MemDC.SetPixel(2*x,2*y,COLOR_DISPLAY);
				MemDC.SetPixel(2*x+1,2*y,COLOR_DISPLAY);
				MemDC.SetPixel(2*x,2*y+1,COLOR_DISPLAY);
				MemDC.SetPixel(2*x+1,2*y+1,COLOR_DISPLAY);
			}
		}
	}

	pControlDC->BitBlt(0, 0, nWidth, nHeight, &MemDC,0,0,SRCCOPY);
	MemDC.DeleteDC();

	ReleaseDC(pControlDC);
}

void CSimulatorDlg::OnBnClickedButtonUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_UP);
}

void CSimulatorDlg::OnBnClickedButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_DOWN);
}

void CSimulatorDlg::OnBnClickedButtonLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_LEFT);
}

void CSimulatorDlg::OnBnClickedButtonRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_RIGHT);
}

void CSimulatorDlg::OnBnClickedButtonPower()
{
	//TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pRadio = new RadioStation((void *)this);
	m_pRadio->PowerOn();
	//return;
	m_pRadio->SelfCheck();
	m_pRadio->MainWindow();

	

	m_rssi = RSSI_4;
	m_battery = BATTERY_0;
	CTime tm;
	tm=CTime::GetCurrentTime();
	m_hour = tm.GetHour();
	m_minute = tm.GetMinute();
	m_pRadio->m_pTitleBar->SetTime(m_hour, m_minute);

	//SetTimer(0,1000,0);
	//SetTimer(1,3*1000,0);
	//SetTimer(2,60*1000,0);
}

void CSimulatorDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��2/����+��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_2);
}

void CSimulatorDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��7/����-��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_7);
}

void CSimulatorDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��3/�ŵ�+��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_3);
}

void CSimulatorDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��8/�ŵ�-��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_8);
}

void CSimulatorDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��4/����+��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_4);
}

void CSimulatorDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��9/����-��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_9);
}

void CSimulatorDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��5/ģʽ��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_5);
}

void CSimulatorDlg::OnBnClickedButton0()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��0/���á�
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_0);
}

void CSimulatorDlg::OnBnClickedButtonMenu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��MENU/ENTER��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_ENTER);
}

void CSimulatorDlg::OnBnClickedButtonBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��back��
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_BACK);
}

void CSimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
	if (nIDEvent == 0){
		if (m_rssi != 0){
			m_rssi --;
		}
		else{
			m_rssi = RSSI_4;
		}
		m_pRadio->m_pTitleBar->SetSignal(CHL_1, m_rssi);
		Draw();
	}
	else if (nIDEvent == 1){
		if (m_battery != BATTERY_3){
			m_battery ++;
		}
		else {
			m_battery = BATTERY_0;
		}
		m_pRadio->m_pTitleBar->SetBattery(m_battery);
		Draw();
	}
	else if (nIDEvent == 2){
		CTime tm;
		tm=CTime::GetCurrentTime();
		m_hour = tm.GetHour();
		m_minute = tm.GetMinute();
		m_pRadio->m_pTitleBar->SetTime(m_hour, m_minute);
	}
}

void CSimulatorDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_1);
}


void CSimulatorDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_6);
}


void CSimulatorDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_pRadio != NULL){
		delete m_pRadio;
		m_pRadio = NULL;
	}
	CDialogEx::OnClose();
}
