#pragma once
#include"CONSTANT.h"
#include "global.h"
#include "GameControl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "Config.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(const CString& cstr,CWnd* pParent = NULL);
	CGameDlg(CConfig *pCg,const CString& cstr, CWnd* pParent = NULL);
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
private:
	//类必要属性
	CDC m_dcMem;//视频内存
	CDC m_dcBG;//背景图DC
	CDC m_dcElement;//地图元素DC
	CDC m_dcMask;//掩码DC
	CDC m_dcPause;//暂停画面

	CPoint m_ptGame;//游戏区域开始位置
	CSize m_sizeElement;//图片大小
	CRect m_gameRect;//游戏矩形大小
	CString m_strCaption;//类名

	//辅助控制部分
	Vertex m_mapSize;//游戏地图大小
	CGameControl *m_gameCM;//游戏控制器
	CConfig* pConfig;//游戏配置
	//音乐播放
	static DWORD WINAPI MusicThread(LPVOID lpParam);
	HANDLE musicHandle;
	DWORD musicID;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//自定义部分
	void InitElement();//将游戏元素图片加载到程序中
	void InitBackground();//初始化背景图片
	void initGameProgress();//初始进度条资源
	void drawTipFrame(int Row,int Col);//为所选元素周围绘制矩形框
	void drawGameTime();//绘制游戏剩余时间

	void drawTipLine(LN pNode[MAXLNNUM]);//绘制连接线
	void drawScore();//绘制积分信息
	int calScore();//结算进度条分数
	CString getGameOverMes(int nModel);//获取输出信息

	void updateTheme();//更新主题
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();


private:
	void updateGameMap();//绘制游戏地图
public:
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonResort();
	afx_msg void OnBnClickedButtonTips();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonHelp();

	void setGameModel(CGameControl* gameModel);//设置游戏模式
	CStatic m_Score;
	afx_msg void OnBnClickedButtonTool();
	afx_msg void OnBnClickedButtonLevel();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnClose();
};
