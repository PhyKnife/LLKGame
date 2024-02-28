#pragma once
#include "Config.h"

// CBKOptionDlg 对话框

class CBKOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBKOptionDlg)

public:
	CBKOptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBKOptionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_BK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CConfig *pConfig;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strBGPPath;
	afx_msg void OnClickedRadio(UINT uID);
	afx_msg void OnBnClickedBtbkPicloc();
	afx_msg void OnEnChangeEditPic();
	void setConfig(CConfig* pCg);
};
