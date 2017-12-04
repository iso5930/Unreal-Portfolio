#pragma once

// CMySheet

#include "MyPage.h"

class CMySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMySheet)

public:
	CMyPage m_MyPage;

public:
	CMySheet();
	CMySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CMySheet();

protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog() override;

};