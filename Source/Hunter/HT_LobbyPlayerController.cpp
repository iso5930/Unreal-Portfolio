// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_LobbyPlayerController.h"
#include "HT_GameInstance.h"
#include <UserWidget.h>
#include <ScrollBox.h>
#include "HT_CharacterSlotWidget.h"
#include "HT_CharacterSelectWidget.h"

void AHT_LobbyPlayerController::FindUserCharacter_Implementation(const FString& UserID)
{
	//플레이어의 정보를 찾자!.

	FString FullPath = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameSavedDir(), TEXT("USER INFO/"), *UserID, TEXT(".txt"));

	TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

	UE_LOG(LogClass, Warning, TEXT("%s"), *FullPath);

	TArray<FCharacter_Info> InfoArr;

	if (FileReader.IsValid())
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("파일 있음"));

		int Cnt;

		*FileReader.Get() << Cnt;

		UE_LOG(LogClass, Warning, TEXT("%s%d"), TEXT("플레이어 숫자 : "), Cnt);

		for (int i = 0; i < Cnt; ++i)
		{
			FCharacter_Info CharacterInfo;

			*FileReader.Get() << CharacterInfo.Name;
			*FileReader.Get() << CharacterInfo.Level;
			*FileReader.Get() << CharacterInfo.CurExp;
			*FileReader.Get() << CharacterInfo.MaxExp;

			UE_LOG(LogClass, Warning, TEXT("%s%s%s%d"), TEXT("플레이어 이름 : "), *CharacterInfo.Name, TEXT("플레이어 레벨 : "), CharacterInfo.Level);

			InfoArr.Add(CharacterInfo);
		}
	}

	CharacterInfoRecv(InfoArr);
}

bool AHT_LobbyPlayerController::FindUserCharacter_Validate(const FString& UserID)
{
	return true;
}

void AHT_LobbyPlayerController::CharacterInfoRecv_Implementation(const TArray<FCharacter_Info>& Characters)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	UScrollBox* ScrollBox = Cast<UScrollBox>(GameInstance->CharacterSelectWidget->GetWidgetFromName("CharacterSlotList"));

	GameInstance->CharacterData.Empty();

	if (Characters.Num() != 0)
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("캐릭터 정보 잇음 추가"));

		for (int i = 0; i < Characters.Num(); ++i)
		{
			UHT_CharacterSlotWidget* CharacterSlotWidget = CreateWidget<UHT_CharacterSlotWidget>(GetWorld(), CharacterSlotWidgetClass);

			if (CharacterSlotWidget != NULL)
			{
				ScrollBox->AddChild(Cast<UWidget>(CharacterSlotWidget));
			}
			
			CharacterSlotWidget->SetSlot(Characters[i]);
			CharacterSlotWidget->index = i;

			GameInstance->CharacterData.Add(Characters[i]);
		}

		if (Characters.Num() < 4)
		{
			for (int i = Characters.Num(); i < 4; ++i)
			{
				UHT_CharacterSlotWidget* CharacterSlotWidget = CreateWidget<UHT_CharacterSlotWidget>(GetWorld(), CharacterSlotWidgetClass);

				if (CharacterSlotWidget != NULL)
				{
					ScrollBox->AddChild(Cast<UWidget>(CharacterSlotWidget));
				}

				CharacterSlotWidget->SetSlot(FCharacter_Info());
				CharacterSlotWidget->index = i;
			}
		}
	}
	else
	{
		// 캐릭터 정보가 없을때.

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("캐릭터 정보 없음"));

		if (ScrollBox != NULL)
		{
			for (int i = 0; i < 4; ++i)
			{
				UHT_CharacterSlotWidget* CharacterSlotWidget = CreateWidget<UHT_CharacterSlotWidget>(GetWorld(), CharacterSlotWidgetClass);

				if (CharacterSlotWidget != NULL)
				{
					ScrollBox->AddChild(Cast<UWidget>(CharacterSlotWidget));
				}

				CharacterSlotWidget->SetSlot(FCharacter_Info());
				CharacterSlotWidget->index = i;
			}
		}
	}
}

void AHT_LobbyPlayerController::CharacterNameCheck_Implementation(const FString& Name, E_WEAPON_TYPE StartWeaponType)
{
	FString FullPath = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameSavedDir(), TEXT("Character/"), *Name, TEXT(".txt"));

	UE_LOG(LogClass, Warning, TEXT("%s"), *FullPath);

	TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

	if (!FileReader.IsValid())
	{
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

		for (int j = 0; j < 17; ++j)
		{
			Inventory[j].Item_Num = j;
		}

		int InventorySize = Inventory.Num();

		if (ArWriter)
		{
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

		CharacterNameCheckRecv(true, Name);
	}
	else
	{
		FileReader->Close();

		CharacterNameCheckRecv(false, Name);
	}
}

bool AHT_LobbyPlayerController::CharacterNameCheck_Validate(const FString& Name, E_WEAPON_TYPE StartWeaponType)
{
	return true;
}

void AHT_LobbyPlayerController::CharacterNameCheckRecv_Implementation(bool IsCheck, const FString& Name)
{
	if (IsCheck)
	{
		UE_LOG(LogClass, Warning, TEXT("%s %s"), TEXT("캐릭터 셀렉트 위젯 추가."), *Name);

		FCharacter_Info Info;

		Info.Name = Name;
		Info.Level = 1;

		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

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
	else
	{
		UE_LOG(LogClass, Warning, TEXT("%s %s"), TEXT("캐릭터 이름이 중복 됩니다."), *Name);
	}
}

void AHT_LobbyPlayerController::BeginPlay()
{
	//게임 인스턴스에 위젯이 안 만들어져 있다면.. Select 위젯 생성.

	Super::BeginPlay();

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Lobby Bigin Player()"));

	if (GetWorld()->IsClient())
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Lobby Bigin Player() 21"));
		
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance != NULL)
		{
			if (GameInstance->CharacterSelectWidget == NULL)
			{
				UUserWidget* CharacterSelectWidget = CreateWidget<UUserWidget>(GetWorld(), CharacterSelectWidgetClass);
				CharacterSelectWidget->AddToViewport();

				if (CharacterSelectWidget != NULL)
				{
					GameInstance->CharacterSelectWidget = CharacterSelectWidget;
				}

				if (GameInstance->IsNetwork == false) //Local일때
				{
					UScrollBox* ScrollBox = Cast<UScrollBox>(CharacterSelectWidget->GetWidgetFromName("CharacterSlotList"));

					if (ScrollBox != NULL)
					{
						for (int i = 0; i < 4; ++i)
						{
							UHT_CharacterSlotWidget* CharacterSlotWidget = CreateWidget<UHT_CharacterSlotWidget>(GetWorld(), CharacterSlotWidgetClass);

							if (CharacterSlotWidget != NULL)
							{
								ScrollBox->AddChild(Cast<UWidget>(CharacterSlotWidget));
							}

							CharacterSlotWidget->SetSlot(FCharacter_Info());
							CharacterSlotWidget->index = i;
						}
					}
				}
				else
				{
					FindUserCharacter(GameInstance->UserInfo.ID);
				}
			}
		}
	}	
}