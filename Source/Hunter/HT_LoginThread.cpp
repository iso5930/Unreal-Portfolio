#include "Hunter.h"
#include "HT_LoginThread.h"
#include "RunnableThread.h"
#include "HT_GameInstance.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"

FHT_LoginThread* FHT_LoginThread::Runnable = NULL;

FHT_LoginThread::FHT_LoginThread()
	:StopTaskCounter(0)
{
	Thread = FRunnableThread::Create(this, TEXT("FHT_LoginThread"));
}

FHT_LoginThread::~FHT_LoginThread()
{
	delete Thread;
	Thread = NULL;
}

bool FHT_LoginThread::Init()
{
	return true;
}

uint32 FHT_LoginThread::Run()
{
	while (!IsComplete)
	{
		if (IsInit)
		{
			GameInstance->ChattingSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("Chatting_Socket"), false);

			FString address = TEXT("192.168.0.7");/*TEXT("127.0.0.1");*//*TEXT("116.41.73.61");*/
			int32 port = 9000;
			FIPv4Address IP;
			FIPv4Address::Parse(address, IP);
			
			TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
			addr->SetIp(IP.Value);
			addr->SetPort(port);

			GameInstance->ChattingSocket->Connect(*addr);

			int32 Recv = 0;

			GameInstance->ChattingSocket->Send(((uint8*)(&LoginInfo)), sizeof(LoginInfo), Recv);

			bool IsCheck = false;
			IsSuccess = false;

			while (!IsCheck)
			{
				uint32 Size = 0;

				if (GameInstance->ChattingSocket->HasPendingData(Size))
				{
					IsCheck = true;

					int itv = 0;

					GameInstance->ChattingSocket->Recv(((uint8*)(&IsSuccess)), Recv, itv);
				}
			}

			if (IsSuccess)
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("인증 성공!!"));
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("인증 실패!!"));
			}

			IsComplete = true;
		}
	}

	return 0;
}

void FHT_LoginThread::Stop()
{
	StopTaskCounter.Increment();
}

void FHT_LoginThread::EnsureCompletion()
{
	Stop();

	Thread->WaitForCompletion();
}

HRESULT FHT_LoginThread::JoyInit(MemberInfo Info, UHT_GameInstance* Game_Instance)
{
	LoginInfo = Info;
	GameInstance = Game_Instance;
	IsInit = true;

	return S_OK;
}

void FHT_LoginThread::Shutdown()
{
	if (Runnable != NULL)
	{
		Runnable->EnsureCompletion();
		delete Runnable;
		Runnable = NULL;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Thread 종료!!"));
	}
}

FHT_LoginThread* FHT_LoginThread::GetInstance()
{
	if(Runnable == NULL && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FHT_LoginThread;
	}

	return Runnable;
}