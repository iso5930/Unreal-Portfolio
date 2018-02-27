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

	UE_LOG(LogClass, Warning, TEXT("%s %d"), TEXT("���ο� �÷��̾� ����"), GetNumPlayers());

	if (PlayerNums.Num() != 0)
	{
		int Num = (int)FMath::RandRange((float)GetNumPlayers(), 100.0f) - 1; // 0 ~ 99�� ���� �߻�.

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
	else if (IsBossSpawn && AccTime >= 2.0f && IsCreate == false)
	{
		IsCreate = true;

		TArray<AActor*> ActorList;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorList);

		int iNum = ActorList.Num();

		for (int i = 0; i < iNum; ++i)
		{
			if (ActorList[i]->ActorHasTag(TEXT("BossSpawnPoint")))
			{
				AHT_BaseMonster* Boss = GetWorld()->SpawnActor<AHT_BaseMonster>(BossMonster, ActorList[i]->GetActorLocation(), ActorList[i]->GetActorRotation());

				Boss->SpawnDefaultController();

				UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("���� ���� ��ȯ!"));

				break;
			}
		}
	}
	
	//���Ͱ� �ִ��� ������ üũ. -> ���ٸ� 2������ ���� ����.
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
	IsCreate = false;
	
	/*UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("���� �ʱ�ȭ"));

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Ver 2.1.0"));*/
}