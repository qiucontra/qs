
// SimulatorDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSimulatorDlg 对话框
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


// CSimulatorDlg 消息处理程序

BOOL CSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Layout();
	//DisplayInit();
	//DisplayImage(16,0,14,14,SYSMINRELEASE);
	//DisplayImage(256-40, 4, 29, 16, battery);

	//char aa[] = "中";

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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



// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		//DrawRectangle(SREEN_SX, SREEN_SY, 256*2, 128*2);
		Draw();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	//屏幕
	rc.left = SREEN_SX;
	rc.top = SREEN_SY;
	rc.right = SREEN_SX + SCREEN_W*2;
	rc.bottom = SREEN_SY + SCREEN_H*2;
	GetDlgItem(IDC_STATIC_SCREEN)->MoveWindow(rc);

	//下部按键
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

	//右侧按钮
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

	//方向键
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

	CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;//定义一个位图对象

	#define COLOR_DISPLAY		RGB(0, 0, 0)
	#define COLOR_UNDISPLAY		RGB(0xFF, 0xFF, 0xFF)

	int nWidth = SCREEN_WIDTH*2;
	int nHeight = SCREEN_HEIGHT*2;
	int x=0,y=0;
	unsigned char *buffer = Display::GetScreen();

	//随后建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画 ^_^
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	MemBitmap.CreateCompatibleBitmap(pControlDC, nWidth, nHeight);

	//将位图选入到内存显示设备中
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	//先用背景色将位图清除干净
	//你也可以用自己应该用的颜色
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
	// TODO: 在此添加控件通知处理程序代码
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_UP);
}

void CSimulatorDlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_DOWN);
}

void CSimulatorDlg::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_LEFT);
}

void CSimulatorDlg::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_RIGHT);
}

void CSimulatorDlg::OnBnClickedButtonPower()
{
	//TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	// “2/功率+”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_2);
}

void CSimulatorDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	// “7/功率-”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_7);
}

void CSimulatorDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	// “3/信道+”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_3);
}

void CSimulatorDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	// “8/信道-”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_8);
}

void CSimulatorDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	// “4/音量+”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_4);
}

void CSimulatorDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	// “9/音量-”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_9);
}

void CSimulatorDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//“5/模式”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_5);
}

void CSimulatorDlg::OnBnClickedButton0()
{
	// TODO: 在此添加控件通知处理程序代码
	//“0/设置”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_0);
}

void CSimulatorDlg::OnBnClickedButtonMenu()
{
	// TODO: 在此添加控件通知处理程序代码
	// “MENU/ENTER”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_ENTER);
}

void CSimulatorDlg::OnBnClickedButtonBack()
{
	// TODO: 在此添加控件通知处理程序代码
	// “back”
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_BACK);
}

void CSimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	// TODO: 在此添加控件通知处理程序代码
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_1);
}


void CSimulatorDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pRadio->m_pCurWnd->Handle((void *)m_pRadio, KEY_6);
}


void CSimulatorDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_pRadio != NULL){
		delete m_pRadio;
		m_pRadio = NULL;
	}
	CDialogEx::OnClose();
}
