
// LLKGameDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLLKGameDlg �Ի���



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


// CLLKGameDlg ��Ϣ�������

BOOL CLLKGameDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitMainBackground();//λͼ�������ڴ���
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLLKGameDlg::OnPaint()
{
	/************
	*ע�͵�����δ�����ϵͳ���ɣ�������С��ʱ�����ϵͳ������WM_PAINT��Ϣ
	*�˶δ����ִ�У���һ����С��ʱ���沢����Ҫ�ػ棬��ϵͳ���ᷢ��WM_PAINT��Ϣ��
	*����ע�͵�����δ���
	*********/
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
		CPaintDC cpDC(this);//����DC

		//��λͼ��λͼ�ڴ濽��ֽ��Ƶ�ڴ���ȥ
		cpDC.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

		CDialogEx::OnPaint();
	}
	/**********
	*���ƽ������ʱ�Ļ�ӭ��
	*������ɾ��

	CPaintDC cpDC(this);//���ڻ����豸������
	CFont welcomeFont;//����һ�ֻ�ӭ����

	welcomeFont.CreatePointFont(200, _T("����"));//���������С����ʽ

	CFont* naturalFont;//���滻������ʽ�������ΪĬ��������ʽ��
	//������ѡ���豸������ ����¼ԭʹ�õ�������ʽ
	naturalFont = cpDC.SelectObject(&welcomeFont);
	//PS:���ۺ�ʱ��һ���ǳ�������ѡ��DC������ü�סǰһ����ѡ��DC�Ķ��󣬵�ʹ�����Ӧ�滻��ԭ����

	//���������һЩ���� ����ѡ��֮ǰ��֮�����þ�����Ч
	cpDC.SetTextColor(RGB(255, 0, 0));//������ɫ��ɫ
	cpDC.SetBkColor(RGB(0, 0, 255));//������ɫ��ɫ

	//���ƻ�ӭ�� ��������ʾ��
	CString cstrWel = _T("Welcome to LLKGAME");
	//��ȡӦ���Ƶ�λ��
	RECT sysRect;
	GetClientRect(&sysRect);//��ȡ�ͻ�������
	CSize strCSize;
	strCSize = cpDC.GetTextExtent(cstrWel, cstrWel.GetLength());//��ȡ�ַ����ĸߺͿ�

	int c_X = (sysRect.right - sysRect.left - strCSize.cx) / 2;
	int c_Y = (sysRect.bottom - sysRect.top - strCSize.cy) / 2;

	//cpDC.TextOut(c_X, c_Y, strCSize);
	cpDC.TextOut(c_X, c_Y, cstrWel);//��������

	//��ԭ������ʽ�����豸������
	cpDC.SelectObject(naturalFont);
	*******/
	
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLLKGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/****************
[������]InitMainBackground
[����]λͼ����λͼ�ڴ�DC��
*******************/
void CLLKGameDlg::InitMainBackground()
{
	//����λͼ
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_BITMAP_BG);//����λͼ

	//��������DC
	CClientDC clientDC(this);
	m_dcMem.CreateCompatibleDC(&clientDC);

	//��ͼƬѡ��DC
	m_dcMem.SelectObject(&bmpMain);
}
/**********
[����]����ģʽ��ť���ʱ����ִ�еĲ���
*****/
void CLLKGameDlg::OnClickedButtonBasic()
{
	this->ShowWindow(SW_HIDE);//��ǰ�������������
	//CTestDlg testDlg;
	//testDlg.DoModal();
	CGameControl *gameModel = new CBaseGame();

	//������Ϸ�Ի���
	CGameDlg gameDlg(pConfig,_T("���������� ����ģʽ"));
	gameDlg.setGameModel(gameModel);

	gameDlg.DoModal();
	//��Ϸ�Ի���ִ�н��� ��������ʾ
	
	this->ShowWindow(SW_SHOW);
}

/**********
[����]����ģʽ��ť���ʱ����ִ�еĲ���
*****/
void CLLKGameDlg::OnBnClickedButtonCasual()
{
	this->ShowWindow(SW_HIDE);//��ǰ�������������

	CGameControl* gameControl = new CEasyGame();
 //������Ϸ�Ի���
	CGameDlg gameDlg(pConfig,_T("���������� ����ģʽ"));
	gameDlg.setGameModel(gameControl);

	gameDlg.DoModal();
	//��Ϸ�Ի���ִ�н��� ��������ʾ

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ������ר�õĴ�������
	pConfig = new CConfig();
	pConfig->Load();
}


void CLLKGameDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	delete pConfig;
	CDialogEx::OnClose();
}
