#pragma once
#include"CONSTANT.h"
#include "global.h"
#include "GameControl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Config.h"

// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(const CString& cstr,CWnd* pParent = NULL);
	CGameDlg(CConfig *pCg,const CString& cstr, CWnd* pParent = NULL);
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
private:
	//���Ҫ����
	CDC m_dcMem;//��Ƶ�ڴ�
	CDC m_dcBG;//����ͼDC
	CDC m_dcElement;//��ͼԪ��DC
	CDC m_dcMask;//����DC
	CDC m_dcPause;//��ͣ����

	CPoint m_ptGame;//��Ϸ����ʼλ��
	CSize m_sizeElement;//ͼƬ��С
	CRect m_gameRect;//��Ϸ���δ�С
	CString m_strCaption;//����

	//�������Ʋ���
	Vertex m_mapSize;//��Ϸ��ͼ��С
	CGameControl *m_gameCM;//��Ϸ������
	CConfig* pConfig;//��Ϸ����
	//���ֲ���
	static DWORD WINAPI MusicThread(LPVOID lpParam);
	HANDLE musicHandle;
	DWORD musicID;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//�Զ��岿��
	void InitElement();//����ϷԪ��ͼƬ���ص�������
	void InitBackground();//��ʼ������ͼƬ
	void initGameProgress();//��ʼ��������Դ
	void drawTipFrame(int Row,int Col);//Ϊ��ѡԪ����Χ���ƾ��ο�
	void drawGameTime();//������Ϸʣ��ʱ��

	void drawTipLine(LN pNode[MAXLNNUM]);//����������
	void drawScore();//���ƻ�����Ϣ
	int calScore();//�������������
	CString getGameOverMes(int nModel);//��ȡ�����Ϣ

	void updateTheme();//��������
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();


private:
	void updateGameMap();//������Ϸ��ͼ
public:
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonResort();
	afx_msg void OnBnClickedButtonTips();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonHelp();

	void setGameModel(CGameControl* gameModel);//������Ϸģʽ
	CStatic m_Score;
	afx_msg void OnBnClickedButtonTool();
	afx_msg void OnBnClickedButtonLevel();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnClose();
};
