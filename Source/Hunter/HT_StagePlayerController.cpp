// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StagePlayerController.h"
#include "HT_InventoryWidget.h"
#include "HT_GameInstance.h"
#include "HT_DropItemWidget.h"
#include "HT_StageWidget.h"
#include "HT_EquipInventory_Widget.h"
#include "HT_BaseCharacter.h"
#include "HT_MonsterHpWidget.h"
#include "HT_TakeItemWidget.h"

void AHT_StagePlayerController::SetPlayerNum_Implementation(int Num)
{
	/*PlayerNum = Num;

	AHT_BaseCharacter* pOwner = Cast<AHT_BaseCharacter>(GetPawn());

	if (pOwner != NULL)
	{
		pOwner->PlayerNum = PlayerNum;
	}*/

	//PlayerState
}

void AHT_StagePlayerController::GetPlayerInventory_Implementation(const FString& PlayerName)
{
	FString FullPath = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameSavedDir(), TEXT("Character/") , *PlayerName, TEXT(".txt"));

	TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

	TArray<FItem_Info> InvenData;

	if (FileReader.IsValid())
	{
		int InventorySize = 0;

		*FileReader.Get() << InventorySize;

		for (int i = 0; i < InventorySize; ++i)
		{
			FItem_Info ItemInfo;

			*FileReader.Get() << ItemInfo.Item_Num;
			*FileReader.Get() << ItemInfo.Item_Cnt;

			InvenData.Add(ItemInfo);
		}

		FileReader->Close();
	}

	SetPlayerInventory(InvenData);
}

bool AHT_StagePlayerController::GetPlayerInventory_Validate(const FString& PlayerName)
{
	return true;
}

void AHT_StagePlayerController::SaveInventoryData_Implementation(const TArray<FItem_Info>& InvenData, const FString& Name)
{
	FString FullPath = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameSavedDir(), TEXT("Character/"), *Name, TEXT(".txt"));

	UE_LOG(LogClass, Warning, TEXT("%s%s"), *FullPath, TEXT("Inventory Save"));

	FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);

	if (ArWriter)
	{
		int Size = InvenData.Num();

		*ArWriter << Size;

		for (int i = 0; i < Size; ++i)
		{
			int Num = InvenData[i].Item_Num;
			int Cnt = InvenData[i].Item_Cnt;

			*ArWriter << Num;
			*ArWriter << Cnt;
		}

		ArWriter->Close();

		delete ArWriter;

		ArWriter = NULL;
	}
}

bool AHT_StagePlayerController::SaveInventoryData_Validate(const TArray<FItem_Info>& InvenData, const FString& Name)
{
	return true;
}

void AHT_StagePlayerController::SaveCharacterData_Implementation(const TArray<FCharacter_Info>& CharacterData, const FString& UserID)
{
	FString FullPath = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameSavedDir(), TEXT("USER INFO/"), *UserID, TEXT(".txt"));

	UE_LOG(LogClass, Warning, TEXT("%s%s"), *FullPath, TEXT("Character Data Save"));

	FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);

	//여기서 경험치 저장.

	if (ArWriter)
	{
		FCharacter_Info CharacterInfo;

		int Cnt = CharacterData.Num();

		*ArWriter << Cnt;

		for (int i = 0; i < CharacterData.Num(); ++i)
		{
			CharacterInfo = CharacterData[i];

			*ArWriter << CharacterInfo.Name;
			*ArWriter << CharacterInfo.Level;
			*ArWriter << CharacterInfo.CurExp;
			*ArWriter << CharacterInfo.MaxExp;

			UE_LOG(LogClass, Warning, TEXT("%s%s%s%d"), *CharacterInfo.Name, TEXT(" Character Data Save.. / "), TEXT(" Character Level : "), CharacterInfo.Level);
		}

		ArWriter->Close();

		delete ArWriter;

		ArWriter = NULL;
	}
}

bool AHT_StagePlayerController::SaveCharacterData_Validate(const TArray<FCharacter_Info>& CharacterData, const FString& UserID)
{
	return true;
}

void AHT_StagePlayerController::GetPlayerEquipInventory_Implementation(const FString& PlayerName)
{
	FString FullPath = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameSavedDir(), TEXT("Character/"), *PlayerName, TEXT("_Equip.txt"));

	TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

	TArray<FItem_Info> EquipData;

	if (FileReader.IsValid())
	{
		for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
		{
			FItem_Info ItemInfo;

			*FileReader.Get() << ItemInfo.Item_Num;
			
			EquipData.Add(ItemInfo);
		}

		FileReader->Close();
	}

	SetPlayerEquipInventory(EquipData);
}

bool AHT_StagePlayerController::GetPlayerEquipInventory_Validate(const FString& PlayerName)
{
	return true;
}

void AHT_StagePlayerController::SaveEquipInventoryData_Implementation(const TArray<FItem_Info>& EquipData, const FString& Name)
{
	FString FullPath = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameSavedDir(), TEXT("Character/"), *Name, TEXT("_Equip.txt"));

	UE_LOG(LogClass, Warning, TEXT("%s%s"), *FullPath, TEXT("Character Equip Inventory Save"));

	FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);

	if (ArWriter)
	{
		for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
		{
			int Num = EquipData[i].Item_Num;
			
			*ArWriter << Num;
		}

		ArWriter->Close();

		delete ArWriter;

		ArWriter = NULL;
	}
}

bool AHT_StagePlayerController::SaveEquipInventoryData_Validate(const TArray<FItem_Info>& EquipData, const FString& Name)
{
	return true;
}

void AHT_StagePlayerController::SetPlayerInventory_Implementation(const TArray<FItem_Info>& Inventory)
{
	//걍 위젯에 넘겨주자.

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		GameInstance->UserInventoryWidget->NetworkInventoryLoad(Inventory);
	}
}

void AHT_StagePlayerController::SetPlayerEquipInventory_Implementation(const TArray<FItem_Info>& EquipInventory)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		GameInstance->EquipWidget->NetworkEquipInventoryLoad(EquipInventory);
	}
}

void AHT_StagePlayerController::BeginPlay()
{
	Super::BeginPlay();

	/* 클라이언트에서만 UI를 생성 */

	if (GetWorld()->IsClient() == true) 
	{
		UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), StageWidget);
		NewWidget->AddToViewport();

		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance != NULL)
		{
			GameInstance->UserInventoryWidget = Cast<UHT_InventoryWidget>(NewWidget->GetWidgetFromName("InventoryWidget"));
			GameInstance->UserInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->DropItemWidget = Cast<UHT_DropItemWidget>(NewWidget->GetWidgetFromName("DropItemWidget"));
			GameInstance->DropItemWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->ItemToolTipWidget = Cast<UUserWidget>(NewWidget->GetWidgetFromName("ItemToolTipWidget"));
			GameInstance->ItemToolTipWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->ChattingInputWidget = Cast<UUserWidget>(NewWidget->GetWidgetFromName("ChattingInputWidget"));
			GameInstance->ChattingInputWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->ChattingWidget = Cast<UUserWidget>(NewWidget->GetWidgetFromName("ChattingLogWidget"));

			GameInstance->StageWidet = Cast<UHT_StageWidget>(NewWidget);

			GameInstance->EquipWidget = Cast<UHT_EquipInventory_Widget>(NewWidget->GetWidgetFromName("EquipInventoryWidget"));
			GameInstance->EquipWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->MonsterHpWidget = Cast<UHT_MonsterHpWidget>(NewWidget->GetWidgetFromName("MonsterHpWidget"));
			GameInstance->MonsterHpWidget->SetVisibility(ESlateVisibility::Collapsed);

			GameInstance->PlayerStateWidget = Cast<UHT_PlayerStateWidget>(NewWidget->GetWidgetFromName("PlayerStateWidget"));

			GameInstance->TakeItemWidget = Cast<UHT_TakeItemWidget>(NewWidget->GetWidgetFromName("TakeItemWidget"));
			//GameInstance->TakeItemWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void AHT_StagePlayerController::UnPossess()
{
	if (GetPawn() != NULL && GetWorld()->IsClient())
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Pawn 있음"));

		AHT_BaseCharacter* pPlayer = Cast<AHT_BaseCharacter>(GetPawn());

		pPlayer->DestroyWeapon();

		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance != NULL)
		{
			SaveInventoryData(GameInstance->UserInventoryWidget->InventoryData, GameInstance->CharacterData[GameInstance->CharacterCurIndex].Name);
			SaveEquipInventoryData(GameInstance->EquipWidget->Equip_Data, GameInstance->CharacterData[GameInstance->CharacterCurIndex].Name);
			SaveCharacterData(GameInstance->CharacterData, GameInstance->UserInfo.ID);
		}
	}
}