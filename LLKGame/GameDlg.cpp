// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKGame.h"
#include "GameDlg.h"
#include "HelpDialog.h"
#include "afxdialogex.h"
#include "CONSTANT.h"
#include "GameDifficulty.h"
#include <cmath>
#include"SettingDlg.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化元素开始绘制位置
	m_ptGame.x = STARTLEFTLOC;
	m_ptGame.y = STARTTOPLOC;
	//初始化元素大小
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
}
CGameDlg::CGameDlg(const CString& cstr, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_strCaption = cstr;
	//初始化元素开始绘制位置
	m_ptGame.x = STARTLEFTLOC;
	m_ptGame.y = STARTTOPLOC;
	//初始化元素大小
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
}
CGameDlg::CGameDlg(CConfig *pCg,const CString& cstr, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//初始化元素开始绘制位置
	m_ptGame.x = STARTLEFTLOC;
	m_ptGame.y = STARTTOPLOC;
	//初始化元素大小
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
	m_strCaption = cstr;

	pConfig = pCg;
}
CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
	DDX_Control(pDX, IDC_STATIC_INT, m_Score);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_RESORT, &CGameDlg::OnBnClickedButtonResort)
	ON_BN_CLICKED(IDC_BUTTON_TIPS, &CGameDlg::OnBnClickedButtonTips)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CGameDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CGameDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_TOOL, &CGameDlg::OnBnClickedButtonTool)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CGameDlg::OnBnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CGameDlg::OnBnClickedButtonSet)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CGameDlg 消息处理程序


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();//加载背景
	InitElement();//加载地图

	m_gameCM->setGameDifficulty(MEDIUM);//设置游戏难度 默认游戏难度为中等
	if (GAME_MODEL_BASE == m_gameCM->getGameModel())
	{
		GetDlgItem(IDC_BUTTON_TOOL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GAME_TIME)->ShowWindow(SW_SHOW);
	}
	else if (GAME_MODEL_EASY == m_gameCM->getGameModel())
	{
		GetDlgItem(IDC_BUTTON_TOOL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_INT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GAME_TIME)->ShowWindow(SW_HIDE);
	}
	SetWindowText(m_strCaption);
	//多线程播放背景音乐
	musicHandle = CreateThread(NULL, 0, MusicThread, pConfig, CREATE_SUSPENDED, &musicID);
	if (pConfig->getBgMusic())
	{
		int status = ResumeThread(musicHandle);
		while (status > 1)
		{
			status = ResumeThread(musicHandle);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC cpDC(this); // device context for painting
	 // TODO: 在此处添加消息处理程序代码
	//将位图内存导入视频内存中
	cpDC.BitBlt(0, 0, 1200, 900, &m_dcMem, 0, 0, SRCCOPY);

	// 不为绘图消息调用 CDialogEx::OnPaint()
}

/**********
[功能]初始化游戏背景图片
*************/
void CGameDlg::InitBackground()
{
	//调用API函数加载位图
	CString cstrBGPPath = pConfig->getStrBGPPath();
	HANDLE bmp = ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmpPause= ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//获取当前DC
	CClientDC clientDC(this);
	//创建与当前内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&clientDC);
	m_dcPause.CreateCompatibleDC(&clientDC);
	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);
	m_dcPause.SelectObject(bmpPause);

	//初始化视频内存DC
	m_dcMem.CreateCompatibleDC(&clientDC);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&clientDC, 1200, 900);
	m_dcMem.SelectObject(&bmpMem);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 1200, 900, &m_dcBG, 0, 0, SRCCOPY);
}
/**********
[功能]设置游戏模式
*************/
void CGameDlg::setGameModel(CGameControl* gameModel)
{
	m_gameCM = gameModel;
}
/*********
[功能]将游戏元素加载到程序中
***********/
void CGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC cDC(this);
	CString elementPath = pConfig->getStrElemPath();
	CString maskPath = pConfig->getStrMaskPath();
	//加载Bmp图片资源 以及图片掩码资源 用于取出背景色
	HANDLE hBmpBG = ::LoadImage(NULL, elementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpMask = ::LoadImage(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建兼容内存DC
	m_dcElement.CreateCompatibleDC(&cDC);
	m_dcMask.CreateCompatibleDC(&cDC);
	//将位图及掩码图片导入到DC
	m_dcElement.SelectObject(hBmpBG);
	m_dcMask.SelectObject(hBmpMask);
}
/**********
[函数名]
[功能]初始化进度条
*************/
void CGameDlg::initGameProgress()
{
	int preTimeGrade = (int)sqrt((m_mapSize.col - 2));
	int gameTime = (m_mapSize.row - 2)*(m_mapSize.col - 2) * preTimeGrade;
	//初始化进度条长度
	m_GameProgress.SetRange(0, gameTime);
	//设置进度条步长
	m_GameProgress.SetStep(-1);
	//设置进度条起始位置
	m_GameProgress.SetPos(gameTime);

	//为进度条添加定时器
	SetTimer(PLAY_TIMER_ID, 1000, NULL);//定时器ID为PLAY_TIMER_ID 间隔时间1000ms 回调函数为系统默认
}
/*************
[功能]根据参数初始化游戏元素
************/
void CGameDlg::updateGameMap()
{
	//绘制背景图片
	m_dcMem.BitBlt(0,0,1200,900,&m_dcBG,0,0,SRCCOPY);
	//开始绘制
	for (int i = 0; i < m_mapSize.row; i++)
	{
		for (int j = 0; j <m_mapSize.col; j++)
		{
			//参数说明
			//前两个参数控制绘制位置 第一个为距左端 第二个为距上端
			//然后两个控制绘制长宽，前为宽，后为长
			//控制从何处取
			//再接着控制取图片的位置
			//最后控制取图片的方式
			//m_dcMem.BitBlt(nLeft + j*nWidth, nTop + i*nHeight, nWidth, nHeight, &m_dcElement , m_anMap[i][j] * nWidth ,0, SRCCOPY);

			//与黑白图相或 在背景上显示图片的白色部分 黑全0 白全1
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx,  m_ptGame.y+ i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcMask,m_gameCM->getElement(i,j) * m_sizeElement.cx, 0, SRCPAINT);
			//与原图相与 在背景图上填充白色部分
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcElement, m_gameCM->getElement(i, j) * m_sizeElement.cx, 0, SRCAND);
		}
	}
}

/**************
[功能]为游戏中的元素绘制外框
*******************/
void CGameDlg::drawTipFrame(int nRow,int nCol)
{
	CClientDC cDC(this);//获取当前视频DC

	CBrush brush(RGB(233, 43, 43));//创建画刷

	//确定绘制矩形位置
	CRect rtTipFrame;
	rtTipFrame.left = nCol*m_sizeElement.cx + m_ptGame.x;
	rtTipFrame.top = nRow*m_sizeElement.cy + m_ptGame.y;
	rtTipFrame.right = rtTipFrame.left + m_sizeElement.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElement.cy;

	//绘制矩形
	cDC.FrameRect(rtTipFrame, &brush);
}
/*************
[函数名]drawTipLine
[功能]绘制两图片间的连接线
***************/
void CGameDlg::drawTipLine(LN pNode[MAXLNNUM])
{
	//获取当前DC
	CClientDC cDC(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen* pOldPen = cDC.SelectObject(&penLine);

	int nStartX = m_ptGame.x + pNode[0].col*m_sizeElement.cx + m_sizeElement.cx / 2;
	int nStartY = m_ptGame.y + pNode[0].row*m_sizeElement.cy + m_sizeElement.cy / 2;
		//设置起点
	cDC.MoveTo(nStartX,nStartY);
	for (int i = 1; i < (MAXLNNUM) && (pNode[i].info); i++)
	{
		//绘制连线
		 nStartX = m_ptGame.x + pNode[i].col*m_sizeElement.cx + m_sizeElement.cx / 2;
		 nStartY = m_ptGame.y + pNode[i].row*m_sizeElement.cy + m_sizeElement.cy / 2;

		 //从起点向终点画线
		 cDC.LineTo(nStartX, nStartY);
	}
	//将原画笔返回
	cDC.SelectObject(pOldPen);
}

/**********
[函数名]
[功能]绘制游戏剩余时间 
*************/
void CGameDlg::drawGameTime()
{
	CClientDC pDC(this);//获取绘制环境

	CFont timeFont;
	timeFont.CreatePointFont(200, _T("楷体"));//高度及字体样式
	CFont *oldFont;
	//将字体选入设备环境
	oldFont = pDC.SelectObject(&timeFont);
	//设置字体颜色
	pDC.SetTextColor(RGB(255, 0, 0));
	pDC.SetBkMode(TRANSPARENT);
	//获取文字输出位置
	CRect textRect;
	(GetDlgItem(IDC_GAME_TIME))->GetClientRect(&textRect);
	textRect.left = textRect.right;
	textRect.right += 20;
	//绘制文字
	CString cstr;
	cstr.Format(L"%d s", m_GameProgress.GetPos());
	pDC.TextOut(textRect.left,textRect.top, cstr);
	//将字体还原
	pDC.SelectObject(oldFont);
	//绘制区域
	InvalidateRect(textRect, TRUE);
}
/**********
[函数名]
[功能]绘制积分信息
*************/
void CGameDlg::drawScore()
{
	if (GAME_MODEL_EASY == m_gameCM->getGameModel())
	{
		CFont* captionFont = new CFont();
		captionFont->CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("楷体"));
		m_Score.SetFont(captionFont);

		CString cstr;
		cstr.Format(L"%d", m_gameCM->getScore());

		m_Score.SetWindowTextW(cstr);
	}
}
/*************
[函数名]
[功能]响应开始游戏按钮
***************/
void CGameDlg::OnClickedButtonStart()
{
	m_mapSize = m_gameCM->startGame();//开始游戏
									 //初始化元素区域大小
	m_gameRect.left = m_ptGame.x;
	m_gameRect.top = m_ptGame.y;
	m_gameRect.right = m_gameRect.left + m_mapSize.col*m_sizeElement.cx;
	m_gameRect.bottom = m_gameRect.top + m_mapSize.row*m_sizeElement.cy;

	drawScore();//绘制积分

	if(GAME_MODEL_BASE==m_gameCM->getGameModel())
		initGameProgress();
	//开始绘制
	updateGameMap();
	Invalidate(FALSE);//不擦除背景 在原有基础上进行更新
}
/*************
[函数名]
[功能]响应鼠标点击
***************/
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((point.x <= m_ptGame.x) || (point.y <= m_ptGame.y))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if ((point.x >= m_gameRect.right) || (point.y >= m_gameRect.bottom))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGame.y) / m_sizeElement.cy;//点击图片在数组中的行下标
	int nCol = (point.x - m_ptGame.x) / m_sizeElement.cx;//点击图片在数组中的列下标

	int status = m_gameCM->UserClickMapElement(nRow, nCol);//调用用户点击地图中位置的响应函数
	switch (status)
	{
	case SELECTBLANK:
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}break;
	case FIRSTSELECT:
	{
		drawTipFrame(nRow, nCol);//绘制矩形框
	}break;
	case CLEARSELECT:
	{
		drawTipFrame(nRow, nCol);//绘制矩形框
		drawTipLine(m_gameCM->getLineOfTwoVex());//绘制连线

												//更新游戏地图
		updateGameMap();

		Sleep(200);//使其显示出画线
		InvalidateRect(m_gameRect, FALSE);
		//绘制积分
		drawScore();
		//判断是否游戏结束
		if (m_gameCM->ifGameOver())
		{
			KillTimer(PLAY_TIMER_ID);
			if (IDYES == MessageBox(getGameOverMes(m_gameCM->getGameModel()), _T("结束"), MB_YESNO))
			{
				m_gameCM->saveScore(calScore());
			}
		}

	}break;
	case RESELECT:
	{
		drawTipFrame(nRow, nCol);//绘制矩形框
		InvalidateRect(m_gameRect, FALSE);
	}break;
	case CLEARSELECTUSETOOL:
	{
		drawTipFrame(nRow, nCol);//绘制矩形框
		updateGameMap();
		InvalidateRect(m_gameRect, FALSE);
		//绘制积分
		drawScore();
		//判断是否游戏结束
		if (m_gameCM->ifGameOver())
		{
			KillTimer(PLAY_TIMER_ID);
			if (IDYES == MessageBox(getGameOverMes(m_gameCM->getGameModel()), _T("结束"), MB_YESNO))
			{
				m_gameCM->saveScore(calScore());
			}
		}
	}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

/*************
[函数名]OnBnClickedButtonResort
[功能]响应重排按钮
***************/
void CGameDlg::OnBnClickedButtonResort()
{
	//重排
	m_gameCM->resortMap();
	//更新地图
	updateGameMap();
	//重绘地图
	InvalidateRect(m_gameRect, FALSE);
}


/*************
[函数名]OnBnClickedButtonTips
[功能]提示玩家一对可消除的图片 响应提示
***************/
void CGameDlg::OnBnClickedButtonTips()
{
	Vertex selectLoc;//提示前选中位置
	bool selectStatus;//提示前选中状态
	selectStatus=m_gameCM->ifSelect(&selectLoc);
	//判断是否查找到提示
	if (m_gameCM->getTips())
	{
		//获取顶点集
		LN *node = m_gameCM->getLineOfTwoVex();
		//获取绘制位置
		int lastNodeIndex;
		for (lastNodeIndex = 0; (lastNodeIndex < MAXLNNUM)&&node[lastNodeIndex].info; lastNodeIndex++);
		//更友好
		if (selectStatus)
		{
			if (((selectLoc.row == node[0].row) && (selectLoc.col == node[0].col)) || ((selectLoc.row == node[lastNodeIndex-1].row) && (selectLoc.col == node[lastNodeIndex-1].col)))
				;
			else
			{
				CRect rePaintRect;
				rePaintRect.left = m_ptGame.x + selectLoc.col*m_sizeElement.cx;
				rePaintRect.top = m_ptGame.y + selectLoc.row*m_sizeElement.cy;
				rePaintRect.right = rePaintRect.left + m_sizeElement.cx;
				rePaintRect.bottom = rePaintRect.top + m_sizeElement.cy;
				InvalidateRect(rePaintRect, FALSE);
			}
		}
		//绘制矩形框
		drawTipFrame(node[0].row, node[0].col);
		drawTipFrame(node[lastNodeIndex - 1].row, node[lastNodeIndex-1].col);

		//绘制连线
		drawTipLine(node);
	}
	else//没有可以连接的元素
	{ 
		MessageBox(_T("       没有可连接的两个图像，抱歉...           "), _T("Tips"), MB_OK);
	}
}
/**********
[函数名]
[功能]响应开始暂停按钮
*************/
void CGameDlg::OnBnClickedButtonPause()
{
	int curGameStatus = m_gameCM->changeGameStatus();
	if (curGameStatus == GAME_GOING)
	{
		if(GAME_MODEL_BASE==m_gameCM->getGameModel())
			SetTimer(PLAY_TIMER_ID, 1000, NULL);
		updateGameMap();
		Invalidate(TRUE);
	}
	else if (curGameStatus == GAME_PAUSE)
	{
		if (GAME_MODEL_BASE == m_gameCM->getGameModel())
			KillTimer(PLAY_TIMER_ID);
		m_dcMem.BitBlt(0, 0, 1200, 900, &m_dcPause, 0, 0, SRCCOPY);
		Invalidate(TRUE);
	}
}
/**********
[函数名]
[功能]响应帮助按钮
*************/
void CGameDlg::OnBnClickedButtonHelp()
{
	CHelpDialog helpDialog(m_gameCM->getGameModel());
	if (GAME_MODEL_BASE == m_gameCM->getGameModel())
	{
		KillTimer(PLAY_TIMER_ID);
		helpDialog.DoModal();
		SetTimer(PLAY_TIMER_ID,1000,NULL);
	}
	else if (GAME_MODEL_EASY == m_gameCM->getGameModel())
	{
		helpDialog.DoModal();
	}
}
/**********
[函数名]
[功能]点击道具
*************/
void CGameDlg::OnBnClickedButtonTool()
{
	m_gameCM->setUseTool();
}
/*****************
[函数名]
[功能]响应设置按钮
****************/
void CGameDlg::OnBnClickedButtonSet()
{
	CSettingDlg settingDlg(pConfig);
	if (GAME_MODEL_BASE == m_gameCM->getGameModel())
	{
		KillTimer(PLAY_TIMER_ID);
		if (IDOK == settingDlg.DoModal())
		{
			pConfig->Save();
			updateTheme();
			if (pConfig->getBgMusic())
			{
				while (ResumeThread(musicHandle)>1);
			}
			else
			{
				SuspendThread(musicHandle);
				PlaySound(NULL, NULL, NULL);
			}
		}
		SetTimer(PLAY_TIMER_ID, 1000, NULL);
	}
	else if (GAME_MODEL_EASY == m_gameCM->getGameModel())
	{
		if (IDOK == settingDlg.DoModal())
		{
			pConfig->Save();
			updateTheme();
			if (pConfig->getBgMusic())
			{
				while (ResumeThread(musicHandle) > 1);
			}
			else
			{
				SuspendThread(musicHandle);
				PlaySound(NULL, NULL, NULL);
			}
		}
	}
}
/*****************
[函数名]
[功能]选择游戏难度
****************/
void CGameDlg::OnBnClickedButtonLevel()
{
	CGameDifficulty gameDifficulty;
	INT_PTR status = gameDifficulty.DoModal();
	switch (status)
	{
	case IDC_BUTTON_EASY:
	{
		m_gameCM->setGameDifficulty(EASY);
	}break;
	case IDC_BUTTON_MEDIUM:
	{
		m_gameCM->setGameDifficulty(MEDIUM);
	}break;
	case IDC_BUTTON_DIFFICULTY:
	{
		m_gameCM->setGameDifficulty(DIFFICULT);
	}break;
	}
	OnClickedButtonStart();
}
/**********
[函数名]
[功能]进度条定时器响应
*************/
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAY_TIMER_ID)
	{
		m_GameProgress.StepIt();
	//	drawGameTime();
		if ((m_GameProgress.GetPos() == 0) && !m_gameCM->ifGameOver())
		{
			//游戏失败
			m_gameCM->doAfterGameOver();
			MessageBox(_T("      时间到！游戏失败！！！       "), _T("失败"), NULL);
			KillTimer(PLAY_TIMER_ID);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

/**********
[函数名]
[功能]结算基本模式得分
*************/
int CGameDlg::calScore()
{
	int nModel = m_gameCM->getGameModel();
	switch (nModel)
	{
	case GAME_MODEL_BASE:
	{
		int leaveTime = m_GameProgress.GetPos();
		int timeScore = leaveTime*((int)sqrt((m_mapSize.col - 2)));

		return timeScore + m_gameCM->getScore();
	}break;
	case GAME_MODEL_EASY:
	{
		return m_gameCM->getScore();
	}break;
	default:return 0;
	}	
}

/*****************
[函数名]
[功能]格式化游戏结束后信息
****************/
CString CGameDlg::getGameOverMes(int nModel)
{
	CString gameCal;
	switch (nModel)
	{
	case GAME_MODEL_BASE:
	{
		gameCal.Format(_T("\t基本模式\n\t游戏完成，恭喜您！！！\n\t最终得分:%d\n\n\t是否保存成绩？\n"),calScore());
	}break;
	case GAME_MODEL_EASY:
	{
		gameCal.Format(_T("\t基本模式\n\t游戏完成，恭喜您！！！\n\t最终得分:%d\n\n\t是否保存成绩？\n"), calScore());
	}break;
	default:gameCal.Format(_T(""));
	}
	return gameCal;
}

/*****************
[函数名]
[功能]更新主题
****************/
void CGameDlg::updateTheme()
{
	CString elementPath = pConfig->getStrElemPath();
	CString maskPath = pConfig->getStrMaskPath();
	CString bgpPath = pConfig->getStrBGPPath();

	HANDLE hBmpElement = ::LoadImage(NULL, elementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpMask = ::LoadImage(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpBgp = ::LoadImage(NULL, bgpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElement.SelectObject(hBmpElement);
	m_dcMask.SelectObject(hBmpMask);
	m_dcBG.SelectObject(hBmpBgp);
	m_dcPause.SelectObject(hBmpBgp);

	updateGameMap();
	Invalidate(TRUE);
}

/*****************
[函数名]
[功能]背景音乐播放线程
****************/
DWORD WINAPI CGameDlg::MusicThread(LPVOID lpParam)
{
	
		PlaySound(((CConfig*)lpParam)->getMusicPath(), NULL, SND_ASYNC| SND_LOOP);
		return 0;
}



void CGameDlg::OnClose()
{
	TerminateThread(musicHandle, 0);
	CDialogEx::OnClose();
}
