#include "stdafx.h"
#include "NetworkMgr.h"
#include "MySheet.h"

CNetworkMgr* CNetworkMgr::m_pInst = NULL;

CNetworkMgr::CNetworkMgr()
{
	HANDLE hFile = CreateFile(L"../Member.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == NULL)
	{
		//로드 실패.
	}

	DWORD dwByte = 0;

	while (true)
	{
		MemberInfo Info;

		ReadFile(hFile, &Info, sizeof(MemberInfo), &dwByte, NULL);

		if(dwByte == 0)
			break;

		m_vecMemberInfoDB.push_back(Info);
	}

	CloseHandle(hFile);
}

CNetworkMgr::~CNetworkMgr()
{
	Release();
}

void CNetworkMgr::Init_NetworkMgr(CMySheet* pMySheet)
{
	m_pMySheet = pMySheet;

	int retval;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		m_pMySheet->m_MyPage.AddLog(CString("WSA Error"));
	}

	Listen_SockV4 = socket(AF_INET, SOCK_STREAM, 0);

	if (Listen_SockV4 == INVALID_SOCKET)
	{
		err_display("socket()");
	}

	SOCKADDR_IN serveraddrv4;
	ZeroMemory(&serveraddrv4, sizeof(serveraddrv4));
	serveraddrv4.sin_family = AF_INET;
	serveraddrv4.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddrv4.sin_port = htons(SERVERPORT);
	retval = bind(Listen_SockV4, (SOCKADDR*)&serveraddrv4, sizeof(serveraddrv4));

	if (retval == SOCKET_ERROR)
	{
		err_display("bind()");
	}

	retval = listen(Listen_SockV4, SOMAXCONN);

	if (retval == SOCKET_ERROR)
	{
		err_display("listen()");
	}

	u_long on = 1;

	retval = ioctlsocket(Listen_SockV4, FIONBIO, &on);

	if (retval == SOCKET_ERROR)
	{
		err_display("ioctlsocket()");
	}
}

void CNetworkMgr::err_display(char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	char FullLog[256] = "";

	char szMsg[50] = "[%s] %s";

	sprintf(FullLog, szMsg, (char*)lpMsgBuf);

	m_pMySheet->m_MyPage.AddLog(CString(FullLog));

	LocalFree(lpMsgBuf);
}

void CNetworkMgr::Update()
{
	FD_SET rset, wset;
	SOCKET Client_Sock;
	int addrlen;

	int retval = 0;

	SOCKADDR_IN Clientaddrv4;

	FD_ZERO(&rset);
	FD_ZERO(&wset);
	FD_SET(Listen_SockV4, &rset);

	for (size_t i = 0; i < m_vecSocketInfo.size(); ++i)
	{
		FD_SET(m_vecSocketInfo[i]->sock, &rset);
	}

	timeval Time;
	Time.tv_sec = 0;
	Time.tv_usec = 0;

	retval = select(0, &rset, &wset, NULL, &Time);

	if (retval == SOCKET_ERROR)
	{
		err_display("select()");

		return;
	}

	if (FD_ISSET(Listen_SockV4, &rset))
	{
		addrlen = sizeof(Clientaddrv4);

		Client_Sock = accept(Listen_SockV4, (SOCKADDR*)&Clientaddrv4, &addrlen);

		if (Client_Sock == INVALID_SOCKET)
		{
			err_display("accept()");

			return;
		}
		else
		{
			MemberInfo Info;

			retval = recv(Client_Sock, (char*)&Info, sizeof(MemberInfo), 0);

			bool IsCheck = false;
			bool IsLogin = false;
			bool IsNew = true;

			for (size_t i = 0; i < m_vecMemberInfoDB.size(); ++i)
			{
				if (lstrcmp(Info.ID, m_vecMemberInfoDB[i].ID) == 0)
				{
					IsNew = false;

					if (lstrcmp(Info.PW, m_vecMemberInfoDB[i].PW) == 0)
					{
						IsLogin = true;
					}

					break;
				}
			}

			if (IsNew)
			{
				m_vecMemberInfoDB.push_back(Info);

				IsLogin = true;
			}

			if (IsLogin)
			{
				IsCheck = true;

				retval = send(Client_Sock, (char*)&IsCheck, sizeof(bool), 0);

				char FullLog[256] = "";

				char NewLog[50] = "[TCPv4 서버] 클라이언트 접속 : [%s] : %d";

				sprintf(FullLog, NewLog, inet_ntoa(Clientaddrv4.sin_addr), ntohs(Clientaddrv4.sin_port));

				m_pMySheet->m_MyPage.AddLog(CString(FullLog));

				SOCKET_INFO* pInfo = new SOCKET_INFO;

				pInfo->sock = Client_Sock;
				pInfo->UserInfo = Info;

				m_vecSocketInfo.push_back(pInfo);
			}
			else
			{
				IsCheck = false;

				retval = send(Client_Sock, (char*)&IsCheck, sizeof(bool), 0);

				closesocket(Client_Sock);
			}			
		}
	}

	for (size_t i = 0; i < m_vecSocketInfo.size(); ++i)
	{
		SOCKET_INFO* pInfo = m_vecSocketInfo[i];

		TCHAR buf[BUFSIZE];

		if (FD_ISSET(pInfo->sock, &rset))
		{
			//메세지 전송.
			retval = recv(pInfo->sock, (char*)buf, sizeof(TCHAR) * BUFSIZE, 0);

			m_pMySheet->m_MyPage.AddLog(CString(buf));

			if (retval == 0 || retval == SOCKET_ERROR)
			{
				closesocket(pInfo->sock);

				delete m_vecSocketInfo[i];
				m_vecSocketInfo[i] = NULL;

				vector<SOCKET_INFO*>::iterator iter = m_vecSocketInfo.begin();

				iter += i;

				m_vecSocketInfo.erase(iter);

				continue;
			}

			for (size_t j = 0; j < m_vecSocketInfo.size(); ++j)
			{
				SOCKET_INFO* pInfo2 = m_vecSocketInfo[j];

				retval = send(pInfo2->sock, (char*)buf, sizeof(TCHAR) * BUFSIZE, 0);

				if (retval == SOCKET_ERROR)
				{
					err_display("send()");

					closesocket(pInfo->sock);

					delete m_vecSocketInfo[j];
					m_vecSocketInfo[j] = NULL;

					vector<SOCKET_INFO*>::iterator iter = m_vecSocketInfo.begin();

					iter += j;

					m_vecSocketInfo.erase(iter);

					--j;

					continue;
				}
			}
		}
	}
}

void CNetworkMgr::Release()
{
	//데이터 저장.

	HANDLE hFile = CreateFile(L"../Member.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == NULL)
	{
		//저장 실패.
	}

	DWORD dwByte = 0;

	for (size_t i = 0; i < m_vecMemberInfoDB.size(); ++i)
	{
		WriteFile(hFile, &(m_vecMemberInfoDB[i]), sizeof(MemberInfo), &dwByte, NULL);
	}

	CloseHandle(hFile);

	for (size_t i = 0; i < m_vecSocketInfo.size(); ++i)
	{
		closesocket(m_vecSocketInfo[i]->sock);

		delete m_vecSocketInfo[i];
		m_vecSocketInfo[i] = NULL;
	}

	m_vecSocketInfo.clear();

	closesocket(Listen_SockV4);
	WSACleanup();
}