// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_CharacterSelectWidget.h"
#include "HT_CharacterSlotWidget.h"
#include <ScrollBox.h>
#include "HT_GameInstance.h"

void UHT_CharacterSelectWidget::ReflashSlot(int Index, bool IsCheck)
{
	UScrollBox* ScrollBox = Cast<UScrollBox>(GetWidgetFromName("CharacterSlotList"));

	if (ScrollBox != NULL)
	{
		int Cnt = ScrollBox->GetChildrenCount();

		for (int i = 0; i < Cnt; ++i)
		{
			UHT_CharacterSlotWidget* SlotWidget = Cast<UHT_CharacterSlotWidget>(ScrollBox->GetChildAt(i));

			if (SlotWidget != NULL)
			{
				SlotWidget->SetBackGroundColor(false);
			}
		}

		CurIndex = -1;

		if (IsCheck)
		{
			CurIndex = Index;

			UHT_CharacterSlotWidget* SlotWidget = Cast<UHT_CharacterSlotWidget>(ScrollBox->GetChildAt(Index));

			if (SlotWidget != NULL)
			{
				SlotWidget->SetBackGroundColor(true);
			}
		}
	}
}

void UHT_CharacterSelectWidget::DeleteCharacter()
{
	//캐릭터 삭제.
}

bool UHT_CharacterSelectWidget::OnClickGameStart()
{
	if (CurIndex == -1)
	{
		return false;
	}

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		GameInstance->CharacterCurIndex = CurIndex;

		return true;
	}

	return false;
}