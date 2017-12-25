// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_CharacterSlotWidget.h"

void UHT_CharacterSlotWidget::SetSlot(FCharacter_Info Info)
{
	CharacterInfo = Info;

	UWidget* NameWiget = GetWidgetFromName("TBCharacterName");
	UWidget* LevelWiget = GetWidgetFromName("TBCharacterLevel");
	UWidget* DefaultWiget = GetWidgetFromName("TBDefaultText");
	UWidget* StaticWiget = GetWidgetFromName("TBStaticText");

	if (CharacterInfo.Level == 0) //슬롯에 등록된 정보가 없다면
	{
		if (NameWiget != NULL)
		{
			NameWiget->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (LevelWiget != NULL)
		{
			LevelWiget->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (DefaultWiget != NULL)
		{
			DefaultWiget->SetVisibility(ESlateVisibility::Visible);
		}

		if (StaticWiget != NULL)
		{
			StaticWiget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		if (NameWiget != NULL)
		{
			NameWiget->SetVisibility(ESlateVisibility::Visible);
		}

		if (LevelWiget != NULL)
		{
			LevelWiget->SetVisibility(ESlateVisibility::Visible);
		}

		if (DefaultWiget != NULL)
		{
			DefaultWiget->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (StaticWiget != NULL)
		{
			StaticWiget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UHT_CharacterSlotWidget::NativeConstruct()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
}