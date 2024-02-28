#pragma once
#include "Config.h"

// CThemeOptionDlg �Ի���

class CThemeOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CThemeOptionDlg)

public:
	CThemeOptionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CThemeOptionDlg(CConfig* pConfig,CWnd* pParent = NULL);
	virtual ~CThemeOptionDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_THEME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	DECLARE_MESSAGE_MAP()
protected:
	CConfig *pConfig;
public:
	CString m_strElemPath;
	CString m_strMaskPath;

	afx_msg void OnClickedRadio(UINT uID);
	afx_msg void OnBnClickedBtthemeElement();
	afx_msg void OnBnClickedBtthemeMask();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditElementpath();
	afx_msg void OnEnChangeEditMaskpath();
	void setConfig(CConfig *pConfig);
	int m_nThemeType;
};
