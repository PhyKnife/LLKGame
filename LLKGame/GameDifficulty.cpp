// GameDifficulty.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKGame.h"
#include "GameDifficulty.h"
#include "afxdialogex.h"


// CGameDifficulty 对话框

IMPLEMENT_DYNAMIC(CGameDifficulty, CDialogEx)

CGameDifficulty::CGameDifficulty(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIFFICULT, pParent)
{

}

CGameDifficulty::~CGameDifficulty()
{
}

void CGameDifficulty::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDifficulty, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EASY, &CGameDifficulty::OnBnClickedButtonEasy)
	ON_BN_CLICKED(IDC_BUTTON_MEDIUM, &CGameDifficulty::OnBnClickedButtonMedium)
	ON_BN_CLICKED(IDC_BUTTON_DIFFICULTY, &CGameDifficulty::OnBnClickedButtonDifficulty)
END_MESSAGE_MAP()


// CGameDifficulty 消息处理程序


void CGameDifficulty::OnBnClickedButtonEasy()
{
	EndDialog(IDC_BUTTON_EASY);
}


void CGameDifficulty::OnBnClickedButtonMedium()
{
	EndDialog(IDC_BUTTON_MEDIUM);
}


void CGameDifficulty::OnBnClickedButtonDifficulty()
{
	EndDialog(IDC_BUTTON_DIFFICULTY);
}
