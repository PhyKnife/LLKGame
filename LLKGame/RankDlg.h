#pragma once
#include "afxcmn.h"


// CRankDlg 对话框

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRankDlg();
	afx_msg void OnClickedRadio(UINT nID);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	void DisplayRank(int nModel);//展示排行榜

	DECLARE_MESSAGE_MAP()
public:
	int m_nMode;
	CListCtrl m_lstRank;
	virtual BOOL OnInitDialog();
	
};
