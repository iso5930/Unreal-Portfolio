// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_CharacterSlotWidget.h"
#include "HT_GameInstance.h"
#include "HT_CharacterSelectWidget.h"

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

void UHT_CharacterSlotWidget::SetBackGroundColor(bool Check)
{
	IsCheck = Check;

	if (IsCheck)
	{
		BackGroundColor = FLinearColor(0.5f, 1.0f, 0.0f, 1.0f);
	}
	else
	{
		BackGroundColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void UHT_CharacterSlotWidget::NativeConstruct()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
}

FReply UHT_CharacterSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();

	if (CharacterInfo.Level != 0)
	{
		if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
		{
			if (IsCheck)
			{
				IsCheck = false;
			}
			else
			{
				IsCheck = true;
			}

			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			if (GameInstance != NULL)
			{
				UHT_CharacterSelectWidget* SelectWidget = Cast<UHT_CharacterSelectWidget>(GameInstance->CharacterSelectWidget);

				if (SelectWidget != NULL)
				{
					SelectWidget->ReflashSlot(index, IsCheck);
				}
			}
		}
	}

	
	return Reply;
}