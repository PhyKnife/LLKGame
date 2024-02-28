
// LLKGameDlg.h : ͷ�ļ�
//

#pragma once
#include"Config.h"

// CLLKGameDlg �Ի���
class CLLKGameDlg : public CDialogEx
{
// ����
public:
	CLLKGameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLKGAME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//�û��Զ�������Լ����������ڴ˴�
protected:
	CDC m_dcMem;//λͼ�ڴ�
	void InitMainBackground();//����λͼ
	CConfig *pConfig;
public:
	afx_msg void OnClickedButtonBasic();
	afx_msg void OnBnClickedButtonCasual();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonRank();
	afx_msg void OnBnClickedButtonSet();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};
