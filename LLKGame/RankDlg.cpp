// RankDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKGame.h"
#include "RankDlg.h"
#include "afxdialogex.h"
#include "CONSTANT.h"
#include "global.h"
#include "ScoreLogic.h"

// CRankDlg 对话框

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RANK, pParent)
	, m_nMode(0)
{

}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_BASE, m_nMode);
	DDX_Control(pDX, IDC_LIST_RANK, m_lstRank);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)
	ON_COMMAND_RANGE(IDC_RADIO_BASE, IDC_RADIO_EASY, &CRankDlg::OnClickedRadio)
END_MESSAGE_MAP()


// CRankDlg 消息处理程序


BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_lstRank.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_lstRank.InsertColumn(0, _T("排名"), LVCFMT_CENTER, 80, 0);
	m_lstRank.InsertColumn(1, _T("玩家"), LVCFMT_CENTER, 160, 0);
	m_lstRank.InsertColumn(2, _T("得分"), LVCFMT_CENTER, 80, 0);

	((CButton*)GetDlgItem(IDC_RADIO_BASE))->SetCheck(TRUE);
	DisplayRank(GAME_MODEL_BASE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CRankDlg::DisplayRank(int nModel)
{
	m_lstRank.DeleteAllItems();
	RankArray rankArray[MAXRANKLEVEL];
	CScoreLogic sLogic;
	int rankNum;
	//根据模式获取展示信息
	rankNum = sLogic.SearchRank(rankArray,nModel);
	CString cRank;
	CString cGrade;

	for (int i = 0; (i < rankNum)&&(i<MAXRANKLEVEL); i++)
	{
		cRank.Format(_T("%d"), i+1);
		m_lstRank.InsertItem(i,cRank);
		m_lstRank.SetItemText(i, 1, rankArray[i].playerName);
		cGrade.Format(_T("%d"), rankArray[i].nGrade);
		m_lstRank.SetItemText(i, 2, cGrade);
	}
}
void CRankDlg::OnClickedRadio(UINT nID)
{
	switch (nID)
	{
	case IDC_RADIO_BASE:
	{
		DisplayRank(GAME_MODEL_BASE);
	}break;
	case IDC_RADIO_EASY:
	{
		DisplayRank(GAME_MODEL_EASY);
	}break;
	default:break;
	}
}

