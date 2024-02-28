#pragma once
#include "afxcmn.h"
#include "ThemeOptionDlg.h"
#include "BKOptionDlg.h"
#include "MusicOptionDlg.h"
#include "Config.h"
// CSettingDlg �Ի���

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CConfig* config,CWnd* pParent = NULL);
	CSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSettingDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CConfig *pConfig;
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabSetting;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();

protected:
	CThemeOptionDlg m_dlgTheme;//�������öԻ���
	CBKOptionDlg m_dlgBK;//�������öԻ���
	CMusicOptionDlg m_dlgMusic;//��Ч���öԻ���
public:
	afx_msg void OnTcnSelchangeTabSetting(NMHDR *pNMHDR, LRESULT *pResult);
};
