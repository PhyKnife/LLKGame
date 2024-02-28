#pragma once
#include "afxcmn.h"
#include "ThemeOptionDlg.h"
#include "BKOptionDlg.h"
#include "MusicOptionDlg.h"
#include "Config.h"
// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CConfig* config,CWnd* pParent = NULL);
	CSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CConfig *pConfig;
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabSetting;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

protected:
	CThemeOptionDlg m_dlgTheme;//主题设置对话框
	CBKOptionDlg m_dlgBK;//背景设置对话框
	CMusicOptionDlg m_dlgMusic;//音效设置对话框
public:
	afx_msg void OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult);
};
