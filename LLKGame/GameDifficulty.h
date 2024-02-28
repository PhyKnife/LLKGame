#pragma once


// CGameDifficulty 对话框

class CGameDifficulty : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDifficulty)

public:
	CGameDifficulty(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDifficulty();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIFFICULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEasy();
	afx_msg void OnBnClickedButtonMedium();
	afx_msg void OnBnClickedButtonDifficulty();
};
