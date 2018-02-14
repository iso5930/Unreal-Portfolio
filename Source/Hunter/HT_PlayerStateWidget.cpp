// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_PlayerStateWidget.h"
#include "HT_BaseCharacter.h"

void UHT_PlayerStateWidget::SetOwnerPlayer(AHT_BaseCharacter* Player)
{
	OwnerPlayer = Player;
}

void UHT_PlayerStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
		
	if (OwnerPlayer != NULL)
	{
		HpPersent = OwnerPlayer->Health / OwnerPlayer->MaxHealth * 100;

		HpPersent /= 100.0f;

		HpString = FString::Printf(TEXT("%d%s%d"), (int)OwnerPlayer->Health, TEXT(" / "), (int)OwnerPlayer->MaxHealth);
	}
}