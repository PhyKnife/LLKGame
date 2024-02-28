// BKOptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLKGame.h"
#include "BKOptionDlg.h"
#include "afxdialogex.h"
#include "Config.h"

// CBKOptionDlg �Ի���

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


// CBKOptionDlg ��Ϣ�������


BOOL CBKOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	((CButton *)GetDlgItem(pConfig->getBGPStyle()))->SetCheck(TRUE);
	m_strBGPPath.Format(_T("%s"), pConfig->getStrBGPPath());
	UpdateData(FALSE);
	if (pConfig->getBGPStyle() == IDC_RADIO_MYBK)
	{
		GetDlgItem(IDC_BTBK_PICLOC)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PIC)->EnableWindow(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
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
	CFileDialog  fileMenu(TRUE, _T("*.bmp"), _T("*"), OFN_OVERWRITEPROMPT, _T("�����ļ�(*.*;)|*.*||"), NULL);
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	UpdateData(FALSE);
	pConfig->setBGPStyle(IDC_RADIO_MYBK);
	pConfig->setStrBGPPath(m_strBGPPath);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
void CBKOptionDlg::setConfig(CConfig* pCg)
{
	pConfig = pCg;
}