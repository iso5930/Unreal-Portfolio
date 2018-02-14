// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StagePlayerState.h"
#include "HT_BaseCharacter.h"
#include "HT_GameInstance.h"

void AHT_StagePlayerState::ClientSetPlayerNum_Implementation(int Num)
{
	ClientPlayerNum = Num;

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		GameInstance->PlayerNum = Num;
	}

	/*AHT_BaseCharacter* pOwner = Cast<AHT_BaseCharacter>(GetOwner());

	if (pOwner != NULL)
	{
		pOwner->PlayerNum = Num;

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("PlayerNum ¼³Á¤"));
	}*/
} 