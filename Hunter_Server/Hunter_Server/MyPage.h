#pragma once


// CMyPage ��ȭ �����Դϴ�.

class CMyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage)

public:
	CMyPage();
	virtual ~CMyPage();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strLog;

public:
	void AddLog(CString NewLog);
	afx_msg void OnBnClickedButton1();
};
