// MySheet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Hunter_Server.h"
#include "MySheet.h"


// CMySheet

IMPLEMENT_DYNAMIC(CMySheet, CPropertySheet)

CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CMySheet::CMySheet()
{
	AddPage(&m_MyPage);
}

CMySheet::~CMySheet()
{

}

BOOL CMySheet::OnInitDialog()
{
	BOOL IsResult = CPropertySheet::OnInitDialog();

	SetActivePage(&m_MyPage);

	return IsResult;
}

BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
END_MESSAGE_MAP()


// CMySheet 메시지 처리기입니다.
