// MyPage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Hunter_Server.h"
#include "MyPage.h"
#include "afxdialogex.h"


// CMyPage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyPage, CPropertyPage)

CMyPage::CMyPage()
	: CPropertyPage(IDD_MYPAGE)
	, m_strLog(_T(""))
{

}

CMyPage::~CMyPage()
{
}

void CMyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Log, m_strLog);
}

void CMyPage::AddLog(CString NewLog)
{
	UpdateData(TRUE);

	if (m_strLog.GetLength() == 0)
	{
		m_strLog = NewLog;
	}
	else
	{
		CString strLog = m_strLog + "\r\n" + NewLog;

		m_strLog = strLog;
	}

	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CMyPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyPage::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyPage �޽��� ó�����Դϴ�.


void CMyPage::OnBnClickedButton1()
{
	//AddLog(CString());
}