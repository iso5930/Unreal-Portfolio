// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_CharacterCreateWidget.h"
#include "HT_CharacterSlotWidget.h"
#include "HT_GameInstance.h"
#include <ScrollBox.h>
#include "HT_DropItem.h"
#include "HT_LobbyPlayerController.h"

void UHT_CharacterCreateWidget::CreateCharacter(FString Name)
{
	FCharacter_Info Info;

	Info.Name = Name;
	Info.Level = 1;

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		if (GameInstance->IsNetwork)
		{
			/*

			�÷��̾� ��Ʈ�ѷ��� Name�� ������ �ߺ����� �ƴ��� �Ǵ��ϰ�, �ߺ��� �ƴ϶��

			/USER ID/User.txt�� Name�� �߰��ϰ�

			/Character/Name.txt�� �����ϰ� �κ��丮 ������ ����.

			*/

			//�켱 �÷��̾� ��Ʈ�ѷ��� ��������.

			AHT_LobbyPlayerController* PlayerController = Cast<AHT_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());

			if (PlayerController != NULL)
			{
				PlayerController->CharacterNameCheck(Name, StartWeaponType);
			}
		}
		else
		{
			LocalCharacterCreate(Info);
		}
	}
}

void UHT_CharacterCreateWidget::LocalCharacterCreate(FCharacter_Info Info)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		/*
		���� ������ ĳ���� ������ ����.
		���� �������� ĳ���� ����ȭ.
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

				ĳ�� ���̵�.txt �ִ� ����.

				FCharacter_Info

				vector<FItem_Info>

				*/

				FString FullPath = FString::Printf(TEXT("%s%s%s"), *FPaths::GameSavedDir(), *Info.Name, TEXT(".txt"));

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

					StartWeapon.Item_Num = 6;

					break;

				case E_WEAPON_TYPE::WEAPON_DUAL_BLADE:

					StartWeapon.Item_Num = 7;

					break;
				}

				//Inventory[0] = StartWeapon;

				/*Inventory[0].Item_Num = 6;
				Inventory[1].Item_Num = 7;
				Inventory[2].Item_Num = 8;
				Inventory[3].Item_Num = 9;
				Inventory[4].Item_Num = 10;*/

				for (int j = 0; j < 17; ++j)
				{
					Inventory[j].Item_Num = j;
				}

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

						UE_LOG(LogClass, Warning, TEXT("ItemNum %d , Cnt %d"), Inventory[j].Item_Num, Inventory[j].Item_Cnt);
					}

					ArWriter->Close();

					delete ArWriter;

					ArWriter = NULL;
				}

				/*

				//���� �б�.

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