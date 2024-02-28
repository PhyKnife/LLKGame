#pragma once
#include"Config.h"

// CMusicOptionDlg 对话框

class CMusicOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMusicOptionDlg)

public:
	CMusicOptionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMusicOptionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_MUSIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	void setConfig(CConfig* pCg);
protected:
	CConfig *pConfig;
public:
	BOOL m_bBgMusic;
	BOOL m_bSound;
	CString m_strMusicPath;
	BOOL m_nMusicType;
	afx_msg void OnClickedRadio(UINT uID);
	afx_msg void OnBnClickedBtmusicMp3loc();
	afx_msg void OnEnChangeEditMusic();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckBgmusic();
	afx_msg void OnBnClickedCheckSound();
};
