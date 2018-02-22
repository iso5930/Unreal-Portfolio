// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_EquipInventory_Widget.h"
#include "HT_InventorySlotWidget.h"
#include "HT_GameInstance.h"
#include "HT_InventoryDragDropOperation.h"
#include "HT_StagePlayerController.h"
#include "HT_BaseCharacter.h"

void UHT_EquipInventory_Widget::ReflashSlot()
{
	for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
	{
		EquipSlotArray[i]->SlotItem = Equip_Data[i];
		EquipSlotArray[i]->ItemSlotType = E_ITEM_SLOT_TYPE::ITEM_SLOT_EQUIP;
	}
}

void UHT_EquipInventory_Widget::Init_Equip()
{
	Equip_Data.Empty();

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		if (GameInstance->IsNetwork)
		{
			AHT_StagePlayerController* PlayerController = Cast<AHT_StagePlayerController>(GetWorld()->GetFirstPlayerController());

			if (PlayerController != NULL)
			{
				FString CharacterName = GameInstance->CharacterData[GameInstance->CharacterCurIndex].Name;

				//서버로 검사하는 함수 호출.
				PlayerController->GetPlayerEquipInventory(CharacterName);
			}
		}
		else
		{
			LocalEquipInventoryLoad();
		}
	}
}

void UHT_EquipInventory_Widget::LocalEquipInventoryLoad()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		if (GameInstance->CharacterData.Num() <= GameInstance->CharacterCurIndex)
		{
			for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
			{
				Equip_Data.Add(FItem_Info());
			}

			return;
		}

		FString CharacterName = GameInstance->CharacterData[GameInstance->CharacterCurIndex].Name;
		FString FullPath = FString::Printf(TEXT("%s%s%s"), *FPaths::GameSavedDir(), *CharacterName, TEXT("_Equip.txt"));
		TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

		if (FileReader.IsValid())
		{
			for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
			{
				FItem_Info ItemInfo;

				int ItemNum = 0;

				*FileReader.Get() << ItemNum;

				if (ItemNum != -1)
				{
					ItemInfo = GameInstance->Item_DataBase[ItemNum];
				}

				Equip_Data.Add(ItemInfo);
			}

			FileReader->Close();
		}
		else
		{
			for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
			{
				Equip_Data.Add(FItem_Info());
			}
		}
	}

	APawn* Actor = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld())->GetPawn();

	AHT_BaseCharacter* Player = Cast<AHT_BaseCharacter>(Actor);

	if (Player != NULL)
	{
		Player->LoadEquip(Equip_Data);
	}

	ReflashSlot();
}

void UHT_EquipInventory_Widget::NetworkEquipInventoryLoad(TArray<FItem_Info> LoadEquipData)
{
	if (LoadEquipData.Num() != 0)
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance != NULL)
		{
			for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
			{
				FItem_Info ItemInfo;

				if (LoadEquipData[i].Item_Num != -1)
				{
					ItemInfo = GameInstance->Item_DataBase[LoadEquipData[i].Item_Num];
				}

				Equip_Data.Add(ItemInfo);
			}
		}
	}
	else
	{
		for (int i = 0; i < (int)E_EQUIP_SLOT_TYPE::EQUIP_SLOT_END; ++i)
		{
			Equip_Data.Add(FItem_Info());
		}
	}

	APawn* Actor = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld())->GetPawn();

	AHT_BaseCharacter* Player = Cast<AHT_BaseCharacter>(Actor);

	if (Player != NULL)
	{
		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("장비 새로 고침"));

		Player->LoadEquip(Equip_Data);
	}

	ReflashSlot();
}

FReply UHT_EquipInventory_Widget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		TSharedPtr<SWidget> DetectingDrag = this->GetCachedWidget();

		MouseOffSet = InMouseEvent.GetScreenSpacePosition();

		MouseOffSet = InGeometry.AbsoluteToLocal(MouseOffSet);

		if (DetectingDrag.IsValid())
		{
			Reply = Reply.DetectDrag(DetectingDrag.ToSharedRef(), EKeys::LeftMouseButton);
		}
	}

	return Reply;
}

void UHT_EquipInventory_Widget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, InOperation);

	UHT_InventoryDragDropOperation* DragDropOp = NewObject<UHT_InventoryDragDropOperation>(UHT_InventoryDragDropOperation::StaticClass());

	DragDropOp->Pivot = EDragPivot::MouseDown;

	UUserWidget* pWidget = CreateWidget<UUserWidget>(GetWorld(), EquipMoveWidgetClass);

	this->SetVisibility(ESlateVisibility::Collapsed);

	if (DragDropOp)
	{
		DragDropOp->Payload = pWidget;
		DragDropOp->DefaultDragVisual = pWidget;
		DragDropOp->DragOffSet = MouseOffSet;
		DragDropOp->DragType = E_ITEM_DROP_TYPE::ITEM_DROP_EQUIP;

		InOperation = DragDropOp;
	}
}