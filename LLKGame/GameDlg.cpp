// GameDlg.cpp : ʵ���ļ�
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


// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//��ʼ��Ԫ�ؿ�ʼ����λ��
	m_ptGame.x = STARTLEFTLOC;
	m_ptGame.y = STARTTOPLOC;
	//��ʼ��Ԫ�ش�С
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
}
CGameDlg::CGameDlg(const CString& cstr, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_strCaption = cstr;
	//��ʼ��Ԫ�ؿ�ʼ����λ��
	m_ptGame.x = STARTLEFTLOC;
	m_ptGame.y = STARTTOPLOC;
	//��ʼ��Ԫ�ش�С
	m_sizeElement.cx = ELEMENTWIDTH;
	m_sizeElement.cy = ELEMENTHEIGHT;
}
CGameDlg::CGameDlg(CConfig *pCg,const CString& cstr, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//��ʼ��Ԫ�ؿ�ʼ����λ��
	m_ptGame.x = STARTLEFTLOC;
	m_ptGame.y = STARTTOPLOC;
	//��ʼ��Ԫ�ش�С
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

// CGameDlg ��Ϣ�������


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();//���ر���
	InitElement();//���ص�ͼ

	m_gameCM->setGameDifficulty(MEDIUM);//������Ϸ�Ѷ� Ĭ����Ϸ�Ѷ�Ϊ�е�
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
	//���̲߳��ű�������
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC cpDC(this); // device context for painting
	 // TODO: �ڴ˴������Ϣ����������
	//��λͼ�ڴ浼����Ƶ�ڴ���
	cpDC.BitBlt(0, 0, 1200, 900, &m_dcMem, 0, 0, SRCCOPY);

	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}

/**********
[����]��ʼ����Ϸ����ͼƬ
*************/
void CGameDlg::InitBackground()
{
	//����API��������λͼ
	CString cstrBGPPath = pConfig->getStrBGPPath();
	HANDLE bmp = ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmpPause= ::LoadImage(NULL, cstrBGPPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��ȡ��ǰDC
	CClientDC clientDC(this);
	//�����뵱ǰ�ڴ���ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&clientDC);
	m_dcPause.CreateCompatibleDC(&clientDC);
	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(bmp);
	m_dcPause.SelectObject(bmpPause);

	//��ʼ����Ƶ�ڴ�DC
	m_dcMem.CreateCompatibleDC(&clientDC);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&clientDC, 1200, 900);
	m_dcMem.SelectObject(&bmpMem);
	//���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, 1200, 900, &m_dcBG, 0, 0, SRCCOPY);
}
/**********
[����]������Ϸģʽ
*************/
void CGameDlg::setGameModel(CGameControl* gameModel)
{
	m_gameCM = gameModel;
}
/*********
[����]����ϷԪ�ؼ��ص�������
***********/
void CGameDlg::InitElement()
{
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC cDC(this);
	CString elementPath = pConfig->getStrElemPath();
	CString maskPath = pConfig->getStrMaskPath();
	//����BmpͼƬ��Դ �Լ�ͼƬ������Դ ����ȡ������ɫ
	HANDLE hBmpBG = ::LoadImage(NULL, elementPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE hBmpMask = ::LoadImage(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//���������ڴ�DC
	m_dcElement.CreateCompatibleDC(&cDC);
	m_dcMask.CreateCompatibleDC(&cDC);
	//��λͼ������ͼƬ���뵽DC
	m_dcElement.SelectObject(hBmpBG);
	m_dcMask.SelectObject(hBmpMask);
}
/**********
[������]
[����]��ʼ��������
*************/
void CGameDlg::initGameProgress()
{
	int preTimeGrade = (int)sqrt((m_mapSize.col - 2));
	int gameTime = (m_mapSize.row - 2)*(m_mapSize.col - 2) * preTimeGrade;
	//��ʼ������������
	m_GameProgress.SetRange(0, gameTime);
	//���ý���������
	m_GameProgress.SetStep(-1);
	//���ý�������ʼλ��
	m_GameProgress.SetPos(gameTime);

	//Ϊ��������Ӷ�ʱ��
	SetTimer(PLAY_TIMER_ID, 1000, NULL);//��ʱ��IDΪPLAY_TIMER_ID ���ʱ��1000ms �ص�����ΪϵͳĬ��
}
/*************
[����]���ݲ�����ʼ����ϷԪ��
************/
void CGameDlg::updateGameMap()
{
	//���Ʊ���ͼƬ
	m_dcMem.BitBlt(0,0,1200,900,&m_dcBG,0,0,SRCCOPY);
	//��ʼ����
	for (int i = 0; i < m_mapSize.row; i++)
	{
		for (int j = 0; j <m_mapSize.col; j++)
		{
			//����˵��
			//ǰ�����������ƻ���λ�� ��һ��Ϊ����� �ڶ���Ϊ���϶�
			//Ȼ���������ƻ��Ƴ���ǰΪ����Ϊ��
			//���ƴӺδ�ȡ
			//�ٽ��ſ���ȡͼƬ��λ��
			//������ȡͼƬ�ķ�ʽ
			//m_dcMem.BitBlt(nLeft + j*nWidth, nTop + i*nHeight, nWidth, nHeight, &m_dcElement , m_anMap[i][j] * nWidth ,0, SRCCOPY);

			//��ڰ�ͼ��� �ڱ�������ʾͼƬ�İ�ɫ���� ��ȫ0 ��ȫ1
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx,  m_ptGame.y+ i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcMask,m_gameCM->getElement(i,j) * m_sizeElement.cx, 0, SRCPAINT);
			//��ԭͼ���� �ڱ���ͼ������ɫ����
			m_dcMem.BitBlt(m_ptGame.x + j*m_sizeElement.cx, m_ptGame.y + i*m_sizeElement.cy, m_sizeElement.cx, m_sizeElement.cy, &m_dcElement, m_gameCM->getElement(i, j) * m_sizeElement.cx, 0, SRCAND);
		}
	}
}

/**************
[����]Ϊ��Ϸ�е�Ԫ�ػ������
*******************/
void CGameDlg::drawTipFrame(int nRow,int nCol)
{
	CClientDC cDC(this);//��ȡ��ǰ��ƵDC

	CBrush brush(RGB(233, 43, 43));//������ˢ

	//ȷ�����ƾ���λ��
	CRect rtTipFrame;
	rtTipFrame.left = nCol*m_sizeElement.cx + m_ptGame.x;
	rtTipFrame.top = nRow*m_sizeElement.cy + m_ptGame.y;
	rtTipFrame.right = rtTipFrame.left + m_sizeElement.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElement.cy;

	//���ƾ���
	cDC.FrameRect(rtTipFrame, &brush);
}
/*************
[������]drawTipLine
[����]������ͼƬ���������
***************/
void CGameDlg::drawTipLine(LN pNode[MAXLNNUM])
{
	//��ȡ��ǰDC
	CClientDC cDC(this);

	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//������ѡ��DC
	CPen* pOldPen = cDC.SelectObject(&penLine);

	int nStartX = m_ptGame.x + pNode[0].col*m_sizeElement.cx + m_sizeElement.cx / 2;
	int nStartY = m_ptGame.y + pNode[0].row*m_sizeElement.cy + m_sizeElement.cy / 2;
		//�������
	cDC.MoveTo(nStartX,nStartY);
	for (int i = 1; i < (MAXLNNUM) && (pNode[i].info); i++)
	{
		//��������
		 nStartX = m_ptGame.x + pNode[i].col*m_sizeElement.cx + m_sizeElement.cx / 2;
		 nStartY = m_ptGame.y + pNode[i].row*m_sizeElement.cy + m_sizeElement.cy / 2;

		 //��������յ㻭��
		 cDC.LineTo(nStartX, nStartY);
	}
	//��ԭ���ʷ���
	cDC.SelectObject(pOldPen);
}

/**********
[������]
[����]������Ϸʣ��ʱ�� 
*************/
void CGameDlg::drawGameTime()
{
	CClientDC pDC(this);//��ȡ���ƻ���

	CFont timeFont;
	timeFont.CreatePointFont(200, _T("����"));//�߶ȼ�������ʽ
	CFont *oldFont;
	//������ѡ���豸����
	oldFont = pDC.SelectObject(&timeFont);
	//����������ɫ
	pDC.SetTextColor(RGB(255, 0, 0));
	pDC.SetBkMode(TRANSPARENT);
	//��ȡ�������λ��
	CRect textRect;
	(GetDlgItem(IDC_GAME_TIME))->GetClientRect(&textRect);
	textRect.left = textRect.right;
	textRect.right += 20;
	//��������
	CString cstr;
	cstr.Format(L"%d s", m_GameProgress.GetPos());
	pDC.TextOut(textRect.left,textRect.top, cstr);
	//�����廹ԭ
	pDC.SelectObject(oldFont);
	//��������
	InvalidateRect(textRect, TRUE);
}
/**********
[������]
[����]���ƻ�����Ϣ
*************/
void CGameDlg::drawScore()
{
	if (GAME_MODEL_EASY == m_gameCM->getGameModel())
	{
		CFont* captionFont = new CFont();
		captionFont->CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����"));
		m_Score.SetFont(captionFont);

		CString cstr;
		cstr.Format(L"%d", m_gameCM->getScore());

		m_Score.SetWindowTextW(cstr);
	}
}
/*************
[������]
[����]��Ӧ��ʼ��Ϸ��ť
***************/
void CGameDlg::OnClickedButtonStart()
{
	m_mapSize = m_gameCM->startGame();//��ʼ��Ϸ
									 //��ʼ��Ԫ�������С
	m_gameRect.left = m_ptGame.x;
	m_gameRect.top = m_ptGame.y;
	m_gameRect.right = m_gameRect.left + m_mapSize.col*m_sizeElement.cx;
	m_gameRect.bottom = m_gameRect.top + m_mapSize.row*m_sizeElement.cy;

	drawScore();//���ƻ���

	if(GAME_MODEL_BASE==m_gameCM->getGameModel())
		initGameProgress();
	//��ʼ����
	updateGameMap();
	Invalidate(FALSE);//���������� ��ԭ�л����Ͻ��и���
}
/*************
[������]
[����]��Ӧ�����
***************/
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((point.x <= m_ptGame.x) || (point.y <= m_ptGame.y))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	if ((point.x >= m_gameRect.right) || (point.y >= m_gameRect.bottom))
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGame.y) / m_sizeElement.cy;//���ͼƬ�������е����±�
	int nCol = (point.x - m_ptGame.x) / m_sizeElement.cx;//���ͼƬ�������е����±�

	int status = m_gameCM->UserClickMapElement(nRow, nCol);//�����û������ͼ��λ�õ���Ӧ����
	switch (status)
	{
	case SELECTBLANK:
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}break;
	case FIRSTSELECT:
	{
		drawTipFrame(nRow, nCol);//���ƾ��ο�
	}break;
	case CLEARSELECT:
	{
		drawTipFrame(nRow, nCol);//���ƾ��ο�
		drawTipLine(m_gameCM->getLineOfTwoVex());//��������

												//������Ϸ��ͼ
		updateGameMap();

		Sleep(200);//ʹ����ʾ������
		InvalidateRect(m_gameRect, FALSE);
		//���ƻ���
		drawScore();
		//�ж��Ƿ���Ϸ����
		if (m_gameCM->ifGameOver())
		{
			KillTimer(PLAY_TIMER_ID);
			if (IDYES == MessageBox(getGameOverMes(m_gameCM->getGameModel()), _T("����"), MB_YESNO))
			{
				m_gameCM->saveScore(calScore());
			}
		}

	}break;
	case RESELECT:
	{
		drawTipFrame(nRow, nCol);//���ƾ��ο�
		InvalidateRect(m_gameRect, FALSE);
	}break;
	case CLEARSELECTUSETOOL:
	{
		drawTipFrame(nRow, nCol);//���ƾ��ο�
		updateGameMap();
		InvalidateRect(m_gameRect, FALSE);
		//���ƻ���
		drawScore();
		//�ж��Ƿ���Ϸ����
		if (m_gameCM->ifGameOver())
		{
			KillTimer(PLAY_TIMER_ID);
			if (IDYES == MessageBox(getGameOverMes(m_gameCM->getGameModel()), _T("����"), MB_YESNO))
			{
				m_gameCM->saveScore(calScore());
			}
		}
	}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

/*************
[������]OnBnClickedButtonResort
[����]��Ӧ���Ű�ť
***************/
void CGameDlg::OnBnClickedButtonResort()
{
	//����
	m_gameCM->resortMap();
	//���µ�ͼ
	updateGameMap();
	//�ػ��ͼ
	InvalidateRect(m_gameRect, FALSE);
}


/*************
[������]OnBnClickedButtonTips
[����]��ʾ���һ�Կ�������ͼƬ ��Ӧ��ʾ
***************/
void CGameDlg::OnBnClickedButtonTips()
{
	Vertex selectLoc;//��ʾǰѡ��λ��
	bool selectStatus;//��ʾǰѡ��״̬
	selectStatus=m_gameCM->ifSelect(&selectLoc);
	//�ж��Ƿ���ҵ���ʾ
	if (m_gameCM->getTips())
	{
		//��ȡ���㼯
		LN *node = m_gameCM->getLineOfTwoVex();
		//��ȡ����λ��
		int lastNodeIndex;
		for (lastNodeIndex = 0; (lastNodeIndex < MAXLNNUM)&&node[lastNodeIndex].info; lastNodeIndex++);
		//���Ѻ�
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
		//���ƾ��ο�
		drawTipFrame(node[0].row, node[0].col);
		drawTipFrame(node[lastNodeIndex - 1].row, node[lastNodeIndex-1].col);

		//��������
		drawTipLine(node);
	}
	else//û�п������ӵ�Ԫ��
	{ 
		MessageBox(_T("       û�п����ӵ�����ͼ�񣬱�Ǹ...           "), _T("Tips"), MB_OK);
	}
}
/**********
[������]
[����]��Ӧ��ʼ��ͣ��ť
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
[������]
[����]��Ӧ������ť
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
[������]
[����]�������
*************/
void CGameDlg::OnBnClickedButtonTool()
{
	m_gameCM->setUseTool();
}
/*****************
[������]
[����]��Ӧ���ð�ť
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
[������]
[����]ѡ����Ϸ�Ѷ�
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
[������]
[����]��������ʱ����Ӧ
*************/
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAY_TIMER_ID)
	{
		m_GameProgress.StepIt();
	//	drawGameTime();
		if ((m_GameProgress.GetPos() == 0) && !m_gameCM->ifGameOver())
		{
			//��Ϸʧ��
			m_gameCM->doAfterGameOver();
			MessageBox(_T("      ʱ�䵽����Ϸʧ�ܣ�����       "), _T("ʧ��"), NULL);
			KillTimer(PLAY_TIMER_ID);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

/**********
[������]
[����]�������ģʽ�÷�
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
[������]
[����]��ʽ����Ϸ��������Ϣ
****************/
CString CGameDlg::getGameOverMes(int nModel)
{
	CString gameCal;
	switch (nModel)
	{
	case GAME_MODEL_BASE:
	{
		gameCal.Format(_T("\t����ģʽ\n\t��Ϸ��ɣ���ϲ��������\n\t���յ÷�:%d\n\n\t�Ƿ񱣴�ɼ���\n"),calScore());
	}break;
	case GAME_MODEL_EASY:
	{
		gameCal.Format(_T("\t����ģʽ\n\t��Ϸ��ɣ���ϲ��������\n\t���յ÷�:%d\n\n\t�Ƿ񱣴�ɼ���\n"), calScore());
	}break;
	default:gameCal.Format(_T(""));
	}
	return gameCal;
}

/*****************
[������]
[����]��������
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
[������]
[����]�������ֲ����߳�
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
