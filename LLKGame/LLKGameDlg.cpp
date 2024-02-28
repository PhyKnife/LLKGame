
// LLKGameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKGame.h"
#include "LLKGameDlg.h"
#include "afxdialogex.h"
#include "GameDlg.h"
#include "BaseGame.h"
#include "EasyGame.h"
#include "HelpDialog.h"
#include "RankDlg.h"
#include "SettingDlg.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLLKGameDlg 对话框



CLLKGameDlg::CLLKGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LLKGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLLKGameDlg::OnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_CASUAL, &CLLKGameDlg::OnBnClickedButtonCasual)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLLKGameDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CLLKGameDlg::OnBnClickedButtonRank)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CLLKGameDlg::OnBnClickedButtonSet)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLLKGameDlg 消息处理程序

BOOL CLLKGameDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitMainBackground();//位图加载至内存中
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKGameDlg::OnPaint()
{
	/************
	*注释掉的这段代码由系统生成，程序最小化时，如果系统发送了WM_PAINT消息
	*此段代码会执行，但一般最小化时界面并不需要重绘，即系统不会发送WM_PAINT消息，
	*所以注释掉了这段代码
	*********/
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
		CPaintDC cpDC(this);//绘制DC

		//将位图从位图内存拷贝纸视频内存中去
		cpDC.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
	/**********
	*绘制进入程序时的欢迎语
	*迭代后删除

	CPaintDC cpDC(this);//用于绘制设备上下文
	CFont welcomeFont;//定义一种欢迎字体

	welcomeFont.CreatePointFont(200, _T("楷体"));//设置字体大小和样式

	CFont* naturalFont;//被替换字体样式（暂理解为默认字体样式）
	//将字体选入设备环境中 并记录原使用的字体样式
	naturalFont = cpDC.SelectObject(&welcomeFont);
	//PS:无论何时将一个非常备对象选入DC，都最好记住前一个被选入DC的对象，当使用完后，应替换回原对象

	//设置字体的一些属性 字体选入之前或之后设置均可生效
	cpDC.SetTextColor(RGB(255, 0, 0));//文字颜色红色
	cpDC.SetBkColor(RGB(0, 0, 255));//背景颜色蓝色

	//绘制欢迎语 （居中显示）
	CString cstrWel = _T("Welcome to LLKGAME");
	//获取应绘制的位置
	RECT sysRect;
	GetClientRect(&sysRect);//获取客户区矩形
	CSize strCSize;
	strCSize = cpDC.GetTextExtent(cstrWel, cstrWel.GetLength());//获取字符串的高和宽

	int c_X = (sysRect.right - sysRect.left - strCSize.cx) / 2;
	int c_Y = (sysRect.bottom - sysRect.top - strCSize.cy) / 2;

	//cpDC.TextOut(c_X, c_Y, strCSize);
	cpDC.TextOut(c_X, c_Y, cstrWel);//绘制文字

	//将原字体样式导入设备环境中
	cpDC.SelectObject(naturalFont);
	*******/
	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLLKGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/****************
[函数名]InitMainBackground
[功能]位图放入位图内存DC中
*******************/
void CLLKGameDlg::InitMainBackground()
{
	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_BITMAP_BG);//加载位图

	//创建兼容DC
	CClientDC clientDC(this);
	m_dcMem.CreateCompatibleDC(&clientDC);

	//将图片选入DC
	m_dcMem.SelectObject(&bmpMain);
}
/**********
[功能]基本模式按钮点击时，所执行的操作
*****/
void CLLKGameDlg::OnClickedButtonBasic()
{
	this->ShowWindow(SW_HIDE);//当前主程序界面隐藏
	//CTestDlg testDlg;
	//testDlg.DoModal();
	CGameControl *gameModel = new CBaseGame();

	//创建游戏对话框
	CGameDlg gameDlg(pConfig,_T("欢乐连连看 基本模式"));
	gameDlg.setGameModel(gameModel);

	gameDlg.DoModal();
	//游戏对话框执行结束 主界面显示
	
	this->ShowWindow(SW_SHOW);
}

/**********
[功能]休闲模式按钮点击时，所执行的操作
*****/
void CLLKGameDlg::OnBnClickedButtonCasual()
{
	this->ShowWindow(SW_HIDE);//当前主程序界面隐藏

	CGameControl* gameControl = new CEasyGame();
 //创建游戏对话框
	CGameDlg gameDlg(pConfig,_T("欢乐连连看 休闲模式"));
	gameDlg.setGameModel(gameControl);

	gameDlg.DoModal();
	//游戏对话框执行结束 主界面显示

	this->ShowWindow(SW_SHOW);
}


void CLLKGameDlg::OnBnClickedButtonHelp()
{
	CHelpDialog helpDlg(GAME_MAIN_FRAME);

	helpDlg.DoModal();
}


void CLLKGameDlg::OnBnClickedButtonRank()
{
	CRankDlg rankDlg;
	rankDlg.DoModal();
}


void CLLKGameDlg::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	pConfig->Load();
	CSettingDlg settingDlg(pConfig);
	if (IDOK == settingDlg.DoModal())
	{
		pConfig->Save();
	}
}


int CLLKGameDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	pConfig = new CConfig();
	pConfig->Load();
}


void CLLKGameDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	delete pConfig;
	CDialogEx::OnClose();
}
