// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_GameInstance.h"
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Core/Public/HAL/RunnableThread.h"
#include "HT_LoginThread.h"

UHT_GameInstance::UHT_GameInstance()
{
	TArray<TCHAR*> Paths;

	Paths.Add(TEXT("/Game/Weapon/Scythe/Scythe"));
	Paths.Add(TEXT("/Game/Weapon/Dual/Dual"));

	for (int32 i = 0; i < Paths.Num(); ++i)
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(Paths[i]);

		if (WeaponMesh.Object != NULL)
		{
			WeaponMeshs.Add(WeaponMesh.Object);
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("%d %s %s"), i, TEXT("Weapon Mesh Loading Error!"), Paths[i]);
		}
	}
}

void UHT_GameInstance::SetNetwork(bool IsCheck)
{
	IsNetwork = IsCheck;

	if (!IsNetwork)
	{
		FString strID = TEXT("Local Player");
		FString strPW = TEXT("");
		//lstrcpy(UserInfo.ID, *strID);
		//lstrcpy(UserInfo.PW, *strPW);
	}
}

void UHT_GameInstance::Init_Network(FString ID, FString PW)
{
	MemberInfo Info;

	memset(&Info, 0, sizeof(Info));

	for (int i = 0; i < ID.Len(); ++i)
	{
		Info.ID[i] = (*ID)[i];
	}

	for (int i = 0; i < PW.Len(); ++i)
	{
		Info.PW[i] = (*PW)[i];
	}

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