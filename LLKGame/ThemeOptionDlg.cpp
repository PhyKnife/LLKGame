// ThemeOptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKGame.h"
#include "ThemeOptionDlg.h"
#include "afxdialogex.h"
#include "Config.h"


// CThemeOptionDlg 对话框

IMPLEMENT_DYNAMIC(CThemeOptionDlg, CDialogEx)

CThemeOptionDlg::CThemeOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_THEME, pParent)
	, m_strElemPath(_T(""))
	, m_strMaskPath(_T(""))
	, m_nThemeType(0)
{

}
CThemeOptionDlg::CThemeOptionDlg(CConfig *pConfig,CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_THEME, pParent)
	, m_nThemeType(0)
	, m_strElemPath(_T(""))
	, m_strMaskPath(_T(""))
{
	this->pConfig = pConfig;
}

CThemeOptionDlg::~CThemeOptionDlg()
{
}

void CThemeOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ELEMENTPATH, m_strElemPath);
	DDX_Text(pDX, IDC_EDIT_MASKPATH, m_strMaskPath);
	DDX_Radio(pDX, IDC_RADIO_SMILE, m_nThemeType);
}


BEGIN_MESSAGE_MAP(CThemeOptionDlg, CDialogEx)
	ON_COMMAND_RANGE(IDC_RADIO_SMILE,IDC_RADIO_MYTHEME,&CThemeOptionDlg::OnClickedRadio)
	ON_BN_CLICKED(IDC_BTTHEME_ELEMENT, &CThemeOptionDlg::OnBnClickedBtthemeElement)
	ON_BN_CLICKED(IDC_BTTHEME_MASK, &CThemeOptionDlg::OnBnClickedBtthemeMask)
	ON_EN_CHANGE(IDC_EDIT_ELEMENTPATH, &CThemeOptionDlg::OnEnChangeEditElementpath)
	ON_EN_CHANGE(IDC_EDIT_MASKPATH, &CThemeOptionDlg::OnEnChangeEditMaskpath)
END_MESSAGE_MAP()

BOOL CThemeOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton *)GetDlgItem(pConfig->getThemeStyle()))->SetCheck(TRUE);
	m_strElemPath.Format(_T("%s"), pConfig->getStrElemPath());
	m_strMaskPath.Format(_T("%s"), pConfig->getStrMaskPath());
	UpdateData(FALSE);
	if (pConfig->getThemeStyle() == IDC_RADIO_MYTHEME)
	{
		GetDlgItem(IDC_BTTHEME_ELEMENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTTHEME_MASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ELEMENTPATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MASKPATH)->EnableWindow(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
// CThemeOptionDlg 消息处理程序
void CThemeOptionDlg::OnClickedRadio(UINT uID)
{
	switch (uID)
	{
	case IDC_RADIO_SMILE:
	{
		pConfig->setThemeStyle(IDC_RADIO_SMILE);
		pConfig->setStrElemPath(_T("source\\element\\smile.bmp"));
		pConfig->setStrMaskPath(_T("source\\element\\smile_mask.bmp"));
	}break;
	case IDC_RADIO_STAR:
	{
		pConfig->setThemeStyle(IDC_RADIO_STAR);
		pConfig->setStrElemPath(_T("source\\element\\star.bmp"));
		pConfig->setStrMaskPath(_T("source\\element\\star_mask.bmp"));
	}break;
	case IDC_RADIO_MYTHEME:
	{
		pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
		GetDlgItem(IDC_BTTHEME_ELEMENT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTTHEME_MASK)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_ELEMENTPATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_MASKPATH)->EnableWindow(TRUE);
	}break;
	default:break;
	}
}

void CThemeOptionDlg::OnBnClickedBtthemeElement()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), _T("*"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{
		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strElemPath.Format(_T("%s"), strRelPath);
		UpdateData(FALSE);
		pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
		pConfig->setStrElemPath(m_strElemPath);
	}
}


void CThemeOptionDlg::OnBnClickedBtthemeMask()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), _T("*"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{
		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strMaskPath.Format(_T("%s"), strRelPath);
		UpdateData(FALSE);
		pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
		pConfig->setStrMaskPath(m_strMaskPath);
	}
}

void CThemeOptionDlg::OnEnChangeEditElementpath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(FALSE);
	pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
	pConfig->setStrElemPath(m_strElemPath);
	// TODO:  在此添加控件通知处理程序代码
}


void CThemeOptionDlg::OnEnChangeEditMaskpath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(FALSE);
	pConfig->setThemeStyle(IDC_RADIO_MYTHEME);
	pConfig->setStrMaskPath(m_strMaskPath);
	// TODO:  在此添加控件通知处理程序代码
}
void CThemeOptionDlg::setConfig(CConfig *pCg)
{
	pConfig = pCg;
}