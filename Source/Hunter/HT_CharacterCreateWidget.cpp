// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_CharacterCreateWidget.h"
#include "HT_CharacterSlotWidget.h"
#include "HT_GameInstance.h"
#include <ScrollBox.h>

void UHT_CharacterCreateWidget::CreateCharacter(FString Name)
{
	FCharacter_Info Info;

	Info.Name = Name;
	Info.Level = 1;

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		/*
		새로 생성된 캐릭터 데이터 삽입.
		추후 서버에도 캐릭터 동기화.
		*/

		GameInstance->CharacterData.Add(Info);

		UScrollBox* ScrollBox = Cast<UScrollBox>(GameInstance->CharacterSelectWidget->GetWidgetFromName("CharacterSlotList"));

		if (ScrollBox == NULL)
			return;

		int32 Count = ScrollBox->GetChildrenCount();

		for (int i = 0; i < Count; ++i)
		{
			UHT_CharacterSlotWidget* SlotWidget = Cast<UHT_CharacterSlotWidget>(ScrollBox->GetChildAt(i));

			if (SlotWidget->CharacterInfo.Level == 0)
			{
				SlotWidget->SetSlot(Info);

				break;
			}
		}
	}
}