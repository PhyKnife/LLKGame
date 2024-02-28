#pragma once
#include"Config.h"

// CMusicOptionDlg �Ի���

class CMusicOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMusicOptionDlg)

public:
	CMusicOptionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMusicOptionDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_MUSIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
