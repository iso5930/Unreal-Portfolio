// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StageGameMode.h"
#include "HT_StagePlayerController.h"
#include "HT_StagePlayerState.h"

void AHT_StageGameMode::PostLogin(APlayerController* NewPlayer)
{
	//GetNumPlayers();

	Super::PostLogin(NewPlayer);

	UE_LOG(LogClass, Warning, TEXT("%s %d"), TEXT("���ο� �÷��̾� ����"), GetNumPlayers());

	if (PlayerNums.Num() != 0)
	{
		int Num = (int)FMath::RandRange((float)GetNumPlayers(), 100.0f) - 1; // 0 ~ 99�� ���� �߻�.

		/*AHT_StagePlayerController* NewPC = Cast<AHT_StagePlayerController>(NewPlayer);

		NewPC->SetPlayerNum(PlayerNums[Num]);*/

		AHT_StagePlayerState* PlayerState = Cast<AHT_StagePlayerState>(NewPlayer->PlayerState);
		PlayerState->ClientSetPlayerNum(PlayerNums[Num]);

		int Temp = PlayerNums[GetNumPlayers()];
		PlayerNums[GetNumPlayers()] = PlayerNums[Num];
		PlayerNums[Num] = PlayerNums[GetNumPlayers()];

		PlayerCnt = GetNumPlayers();
	}	
}

void AHT_StageGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	//�������� �ε���.. �ƴϴ� �ϴ� ����ȭ ����.

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("�÷��̾� ����"));
}

void AHT_StageGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 100; ++i)
	{
		PlayerNums.Add(i);
	}

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("���� �ʱ�ȭ"));

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Ver 1.1.2"));
}