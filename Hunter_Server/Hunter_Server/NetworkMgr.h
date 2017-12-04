#pragma once

#include <vector>

using namespace std;

struct MemberInfo
{
	TCHAR ID[20];
	TCHAR PW[20];
};

struct SOCKET_INFO
{
	SOCKET	sock;
	MemberInfo UserInfo;
};

class CNetworkMgr
{
private:
	static CNetworkMgr* m_pInst;

public:
	static CNetworkMgr* GetInstance()
	{
		if (m_pInst == NULL)
		{
			m_pInst = new CNetworkMgr;
		}

		return m_pInst;
	}

	void DestoryInstance()
	{
		if (m_pInst != NULL)
		{
			delete m_pInst;
			m_pInst = NULL;
		}
	}

private:
	class CMySheet* m_pMySheet;
	vector<SOCKET_INFO*> m_vecSocketInfo;
	SOCKET Listen_SockV4;
	vector<MemberInfo> m_vecMemberInfoDB;

public:
	void Init_NetworkMgr(CMySheet* pMySheet);
	void err_display(char* msg);

	void Update();

private:
	void Release();

private:
	CNetworkMgr();
	~CNetworkMgr();
};