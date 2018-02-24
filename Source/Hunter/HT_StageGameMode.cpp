// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StageGameMode.h"
#include "HT_StagePlayerController.h"
#include "HT_StagePlayerState.h"
#include "HT_BaseCharacter.h"
#include "HT_BaseMonster.h"

AHT_StageGameMode::AHT_StageGameMode()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHT_StageGameMode::PostLogin(APlayerController* NewPlayer)
{
	//GetNumPlayers();

	Super::PostLogin(NewPlayer);

	UE_LOG(LogClass, Warning, TEXT("%s %d"), TEXT("새로운 플레이어 입장"), GetNumPlayers());

	if (PlayerNums.Num() != 0)
	{
		int Num = (int)FMath::RandRange((float)GetNumPlayers(), 100.0f) - 1; // 0 ~ 99의 난수 발생.

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

	//나간놈의 인덱스.. 아니다 일단 동기화 먼저.

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("플레이어 나감"));
}

void AHT_StageGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AccTime += DeltaSeconds;

	if (AccTime >= 2.0f && IsBossSpawn == false)
	{
		AccTime = 0.0f;

		TArray<AActor*> MonsterList;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHT_BaseMonster::StaticClass(), MonsterList);

		if (MonsterList.Num() == 0)
		{
			IsBossSpawn = true;
		}
	}
	else if (IsBossSpawn && AccTime >= 2.0f)
	{
		//보스 등장.

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("보스 등장!!"));
	}
}

void AHT_StageGameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 100; ++i)
	{
		PlayerNums.Add(i);
	}

	AccTime = 0.0f;

	IsBossSpawn = false;
	
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("난수 초기화"));

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Ver 2.1.0"));
}