// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_CharacterCreateWidget.h"
#include "HT_CharacterSlotWidget.h"
#include "HT_GameInstance.h"
#include <ScrollBox.h>
#include "HT_DropItem.h"

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

				/*
				
				캐릭 아이디.txt 넣는 순서.

				FCharacter_Info

				vector<FItem_Info>

				*/

				FString FullPath = FString::Printf(TEXT("%s%s%s"), *FPaths::GameSavedDir(), *Name, TEXT(".txt"));

				FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);

				TArray<FItem_Info> Inventory;

				for (int j = 0; j < 30; ++j)
				{
					Inventory.Add(FItem_Info());
				}

				FItem_Info StartWeapon;

				
				switch (StartWeaponType)
				{
				case E_WEAPON_TYPE::WEAPON_SCYTHE:

					StartWeapon.Item_Num = 7;

					break;

				case E_WEAPON_TYPE::WEAPON_DUAL_BLADE:

					StartWeapon.Item_Num = 8;

					break;
				}

				Inventory[0] = StartWeapon;

				int InventorySize = Inventory.Num();

				if (ArWriter)
				{
					*ArWriter << Info.Name;
					*ArWriter << Info.Level;
					*ArWriter << InventorySize;

					for (int j = 0; j < 30; ++j)
					{
						*ArWriter << Inventory[j].Item_Num;
						*ArWriter << Inventory[j].Item_Cnt;
					}

					ArWriter->Close();

					delete ArWriter;

					ArWriter = NULL;
				}
				
				/*

				//파일 읽기.

				TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

				if (FileReader.IsValid())
				{
					FCharacter_Info NewInfo;

					*FileReader.Get() << NewInfo.Name;
					*FileReader.Get() << NewInfo.Level;

					UE_LOG(LogClass, Warning, TEXT("Name %s , Level %d"), *NewInfo.Name, NewInfo.Level);

					*FileReader.Get() << InventorySize;

					for (int j = 0; j < InventorySize; ++j)
					{
						*FileReader << Inventory[j].Item_Num;
						*FileReader << Inventory[j].Item_Cnt;
					}

					FileReader->Close();
				}

				*/
				break;
			}
		}
	}
}