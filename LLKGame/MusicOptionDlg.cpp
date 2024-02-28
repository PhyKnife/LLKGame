// MusicOptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKGame.h"
#include "MusicOptionDlg.h"
#include "afxdialogex.h"
#include"Config.h"

// CMusicOptionDlg 对话框

IMPLEMENT_DYNAMIC(CMusicOptionDlg, CDialogEx)

CMusicOptionDlg::CMusicOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_MUSIC, pParent)
	, m_bBgMusic(FALSE)
	, m_bSound(FALSE)
	, m_strMusicPath(_T(""))
	, m_nMusicType(FALSE)
{

}

CMusicOptionDlg::~CMusicOptionDlg()
{
}

void CMusicOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_BGMUSIC, m_bBgMusic);
	DDX_Check(pDX, IDC_CHECK_SOUND, m_bSound);
	DDX_Text(pDX, IDC_EDIT_MUSIC, m_strMusicPath);
	DDX_Radio(pDX, IDC_RADIO_DEFMUSIC, m_nMusicType);
}


BEGIN_MESSAGE_MAP(CMusicOptionDlg, CDialogEx)
	ON_COMMAND_RANGE(IDC_RADIO_DEFMUSIC, IDC_RADIO_MYMUSIC, &CMusicOptionDlg::OnClickedRadio)
	ON_BN_CLICKED(IDC_BTMUSIC_MP3LOC, &CMusicOptionDlg::OnBnClickedBtmusicMp3loc)
	ON_EN_CHANGE(IDC_EDIT_MUSIC, &CMusicOptionDlg::OnEnChangeEditMusic)
	ON_BN_CLICKED(IDC_CHECK_BGMUSIC, &CMusicOptionDlg::OnBnClickedCheckBgmusic)
	ON_BN_CLICKED(IDC_CHECK_SOUND, &CMusicOptionDlg::OnBnClickedCheckSound)
END_MESSAGE_MAP()


// CMusicOptionDlg 消息处理程序
void CMusicOptionDlg::setConfig(CConfig* pCg)
{
	pConfig = pCg;
}
void CMusicOptionDlg::OnClickedRadio(UINT uID)
{
	switch (uID)
	{
	case IDC_RADIO_DEFMUSIC:
	{
		pConfig->setMusicStyle(IDC_RADIO_DEFMUSIC);
		pConfig->setMusicPath(_T("source\\music\\default.mp3"));
	}break;
	case IDC_RADIO_MYMUSIC:
	{
		pConfig->setMusicStyle(IDC_RADIO_MYMUSIC);
		GetDlgItem(IDC_EDIT_MUSIC)->EnableWindow(SW_SHOW);
		GetDlgItem(IDC_BTMUSIC_MP3LOC)->EnableWindow(SW_SHOW);
	}break;
	}
}

void CMusicOptionDlg::OnBnClickedBtmusicMp3loc()
{
	CFileDialog  fileMenu(TRUE, _T("*.mp3"), _T("*"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{

		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strMusicPath.Format(_T("%s"), strRelPath);
		UpdateData(FALSE);
		pConfig->setMusicStyle(IDC_RADIO_MYMUSIC);
		pConfig->setMusicPath(m_strMusicPath);
	}
}


void CMusicOptionDlg::OnEnChangeEditMusic()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(FALSE);
	pConfig->setMusicPath(m_strMusicPath);
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CMusicOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_bBgMusic = pConfig->getBgMusic();
	m_bSound = pConfig->getSound();
	((CButton*)GetDlgItem(pConfig->getMusicStyle()))->SetCheck(TRUE);
	m_strMusicPath.Format(_T("%s"), pConfig->getMusicPath());
	UpdateData(FALSE);
	if (pConfig->getMusicStyle() == IDC_RADIO_MYMUSIC)
	{
		GetDlgItem(IDC_EDIT_MUSIC)->EnableWindow(SW_SHOW);
		GetDlgItem(IDC_BTMUSIC_MP3LOC)->EnableWindow(SW_SHOW);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CMusicOptionDlg::OnBnClickedCheckBgmusic()
{
	if (m_bBgMusic == true)
	{
		m_bBgMusic = false;
	}
	else
		m_bBgMusic = true;
	
	UpdateData(FALSE);
	pConfig->setBgMusic(m_bBgMusic);
}


void CMusicOptionDlg::OnBnClickedCheckSound()
{
	if (m_bSound == true)
	{
		m_bSound = false;
	}
	else
		m_bSound = true;
	UpdateData(FALSE);

	pConfig->setSound(m_bSound);
}
