
// Hunter_Server.h : Hunter_Server ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CHunter_ServerApp:
// �� Ŭ������ ������ ���ؼ��� Hunter_Server.cpp�� �����Ͻʽÿ�.
//

class CHunter_ServerApp : public CWinApp
{
public:
	CHunter_ServerApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnIdle(LONG lCount) override;

};

extern CHunter_ServerApp theApp;
