// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StagePlayerState.h"
#include "HT_BaseCharacter.h"

void AHT_StagePlayerState::ClientSetPlayerNum_Implementation(int Num)
{
	ClientPlayerNum = Num;

	AHT_BaseCharacter* pOwner = Cast<AHT_BaseCharacter>(GetOwner());

	if (pOwner != NULL)
	{
		pOwner->PlayerNum = Num;
	}
}