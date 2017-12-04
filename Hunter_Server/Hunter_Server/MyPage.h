#pragma once


// CMyPage 대화 상자입니다.

class CMyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage)

public:
	CMyPage();
	virtual ~CMyPage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYPAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strLog;

public:
	void AddLog(CString NewLog);
	afx_msg void OnBnClickedButton1();
};
