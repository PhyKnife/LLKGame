#pragma once
#include "afxcmn.h"


// CRankDlg �Ի���

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRankDlg();
	afx_msg void OnClickedRadio(UINT nID);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	void DisplayRank(int nModel);//չʾ���а�

	DECLARE_MESSAGE_MAP()
public:
	int m_nMode;
	CListCtrl m_lstRank;
	virtual BOOL OnInitDialog();
	
};
