#pragma once


// CGameDifficulty �Ի���

class CGameDifficulty : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDifficulty)

public:
	CGameDifficulty(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDifficulty();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIFFICULT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonEasy();
	afx_msg void OnBnClickedButtonMedium();
	afx_msg void OnBnClickedButtonDifficulty();
};
