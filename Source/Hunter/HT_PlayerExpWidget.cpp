// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_PlayerExpWidget.h"
#include "HT_GameInstance.h"

void UHT_PlayerExpWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GameInstance == NULL)
	{
		GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
	}
	else
	{
		ExpPersent = (float)GameInstance->CharacterData[GameInstance->CharacterCurIndex].CurExp / (float)GameInstance->CharacterData[GameInstance->CharacterCurIndex].MaxExp * 100;

		ExpPersent /= 100.0f;
	}
}