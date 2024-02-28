// BKOptionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLKGame.h"
#include "BKOptionDlg.h"
#include "afxdialogex.h"
#include "Config.h"

// CBKOptionDlg 对话框

IMPLEMENT_DYNAMIC(CBKOptionDlg, CDialogEx)

CBKOptionDlg::CBKOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_BK, pParent)
	, m_strBGPPath(_T(""))
{

}

CBKOptionDlg::~CBKOptionDlg()
{
}

void CBKOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PIC, m_strBGPPath);
}


BEGIN_MESSAGE_MAP(CBKOptionDlg, CDialogEx)
	ON_COMMAND_RANGE(IDC_RADIO_GREEN, IDC_RADIO_MYBK, &CBKOptionDlg::OnClickedRadio)
	ON_BN_CLICKED(IDC_BTBK_PICLOC, &CBKOptionDlg::OnBnClickedBtbkPicloc)
	ON_EN_CHANGE(IDC_EDIT_PIC, &CBKOptionDlg::OnEnChangeEditPic)
END_MESSAGE_MAP()


// CBKOptionDlg 消息处理程序


BOOL CBKOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton *)GetDlgItem(pConfig->getBGPStyle()))->SetCheck(TRUE);
	m_strBGPPath.Format(_T("%s"), pConfig->getStrBGPPath());
	UpdateData(FALSE);
	if (pConfig->getBGPStyle() == IDC_RADIO_MYBK)
	{
		GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PIC)->EnableWindow(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CBKOptionDlg::OnClickedRadio(UINT uID)
{
	switch(uID)
	{ 
	case IDC_RADIO_GREEN:
	{
		pConfig->setBGPStyle(IDC_RADIO_GREEN);
		pConfig->setStrBGPPath(_T("source\\bgp\\theme0.bmp"));
	}break;
	case IDC_RADIO_SKY:
	{
		pConfig->setBGPStyle(IDC_RADIO_SKY);
		pConfig->setStrBGPPath(_T("source\\bgp\\theme1.bmp"));
	}break;
	case IDC_RADIO_NIGHT:
	{
		pConfig->setBGPStyle(IDC_RADIO_NIGHT);
		pConfig->setStrBGPPath(_T("source\\bgp\\theme2.bmp"));
	}break;
	case IDC_RADIO_SUNFLOWER:
	{
		pConfig->setBGPStyle(IDC_RADIO_SUNFLOWER);
		pConfig->setStrBGPPath(_T("source\\bgp\\theme3.bmp"));
	}break;
	case IDC_RADIO_MYBK:
	{
		pConfig->setBGPStyle(IDC_RADIO_MYBK);
		GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PIC)->EnableWindow(TRUE);
	}break;
	default:break;
	}
}

void CBKOptionDlg::OnBnClickedBtbkPicloc()
{
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), _T("*"), OFN_OVERWRITEPROMPT, _T("所有文件(*.*;)|*.*||"), NULL);
	if (IDOK == fileMenu.DoModal())
	{

		CString strPath = fileMenu.GetFolderPath();
		CString strName = fileMenu.GetFileName();
		CString strRelPath = strPath + "\\" + strName;
		m_strBGPPath.Format(_T("%s"), strRelPath);
		UpdateData(FALSE);
		pConfig->setBGPStyle(IDC_RADIO_MYBK);
		pConfig->setStrBGPPath(m_strBGPPath);
	}
}


void CBKOptionDlg::OnEnChangeEditPic()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	UpdateData(FALSE);
	pConfig->setBGPStyle(IDC_RADIO_MYBK);
	pConfig->setStrBGPPath(m_strBGPPath);
	// TODO:  在此添加控件通知处理程序代码
}
void CBKOptionDlg::setConfig(CConfig* pCg)
{
	pConfig = pCg;
}