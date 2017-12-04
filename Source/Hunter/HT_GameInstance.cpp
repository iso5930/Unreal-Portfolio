// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_GameInstance.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "HT_LoginThread.h"
#include <Windows.h>

void UHT_GameInstance::SetNetwork(bool IsCheck)
{
	IsNetwork = IsCheck;

	if (!IsNetwork)
	{
		FString strID = TEXT("Local Player");
		FString strPW = TEXT("");
		lstrcpy(UserInfo.ID, *strID);
		lstrcpy(UserInfo.PW, *strPW);
	}
}

void UHT_GameInstance::Init_Network(FString ID, FString PW)
{
	MemberInfo Info;
	ZeroMemory(&Info, sizeof(Info));

	lstrcpy(Info.ID, *ID);
	lstrcpy(Info.PW, *PW);

	UserInfo = Info;

	FHT_LoginThread::GetInstance()->JoyInit(Info, this);
}

void UHT_GameInstance::FinishDestroy()
{
	Super::FinishDestroy();

	if (ChattingSocket != NULL)
	{
		ChattingSocket->Close();
		ChattingSocket = NULL;
	}
}