// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_InventoryWidget.h"
#include "HT_InventorySlotWidget.h"
#include "HT_InventoryDragDropOperation.h"
#include "HT_GameInstance.h"

void UHT_InventoryWidget::ReflashSlot()
{
	for (int i = 0; i < 30; ++i)
	{
		InventorySlotArray[i]->SlotItem = InventoryData[i];
		InventorySlotArray[i]->ItemSlotType = E_ITEM_SLOT_TYPE::ITEM_SLOT_INVENTORY;
	}

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("�κ��丮 ���ΰ�ħ"));
}

void UHT_InventoryWidget::Init_Inventory()
{
	//�켱 ����.
	InventoryData.Empty();

	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("�κ��丮 �ʱ�ȭ"));

	UHT_GameInstance* GameInstance = NULL;

	if (GetWorld() != NULL)
	{
		GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("�κ��丮 1��"));
	}

	if (GameInstance != NULL)
	{
		if (GameInstance->CharacterData.Num() <= GameInstance->CharacterCurIndex)
		{
			for (int i = 0; i < 30; ++i)
			{
				InventoryData.Add(FItem_Info());
			} //�κ��丮 �ʱ�ȭ ����.

			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("�κ��丮 �ҷ����� ����"));

			return;
		}

		FString CharacterName = GameInstance->CharacterData[GameInstance->CharacterCurIndex].Name;

		FString FullPath = FString::Printf(TEXT("%s%s%s"), *FPaths::GameSavedDir(), *CharacterName, TEXT(".txt"));

		TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

		if (FileReader.IsValid())
		{
			FCharacter_Info NewInfo;

			int InventorySize;

			*FileReader.Get() << NewInfo.Name;
			*FileReader.Get() << NewInfo.Level;

			UE_LOG(LogClass, Warning, TEXT("Name %s , Level %d"), *NewInfo.Name, NewInfo.Level);

			*FileReader.Get() << InventorySize;

			for (int i = 0; i < InventorySize; ++i)
			{
				FItem_Info ItemInfo;

				int ItemNum = 0;
				int ItemCnt = 0;

				*FileReader.Get() << ItemNum;
				*FileReader.Get() << ItemCnt;

				UE_LOG(LogClass, Warning, TEXT("ItemNum %d , Cnt %d"), ItemNum, ItemCnt);

				if (ItemNum != -1)
				{
					ItemInfo = GameInstance->Item_DataBase[ItemNum];

					ItemInfo.Item_Cnt = ItemCnt;
				}
				
				InventoryData.Add(ItemInfo);
			}

			FileReader->Close();
		}
		else
		{
			for (int i = 0; i < 30; ++i)
			{
				InventoryData.Add(FItem_Info());
			} //�κ��丮 �ʱ�ȭ ����.
		}
	}
}

void UHT_InventoryWidget::AddItem(FItem_Info NewItemInfo)
{
	if (NewItemInfo.Item_MaxCnt > 1)//�ߺ��� ������ �ִ�.
	{
		int ItemCnt = NewItemInfo.Item_Cnt;

		bool IsCheck = false;

		for (int i = 0; i < InventoryData.Num(); ++i)
		{
			if (InventoryData[i].Item_Name == NewItemInfo.Item_Name)
			{
				if (InventoryData[i].Item_Cnt != InventoryData[i].Item_MaxCnt) //�ƽø��� �ƴҶ�.
				{
					InventoryData[i].Item_Cnt += ItemCnt;

					if (InventoryData[i].Item_Cnt >= InventoryData[i].Item_MaxCnt) //�ѱ�ų� �� ������.
					{
						ItemCnt = InventoryData[i].Item_Cnt - InventoryData[i].Item_MaxCnt;

						InventoryData[i].Item_Cnt = InventoryData[i].Item_MaxCnt;
					}
					else
					{
						ItemCnt = 0;
					}

					if (ItemCnt == 0)
					{
						IsCheck = true;

						break;
					}
				}
			}
		}

		if (IsCheck == false)
		{
			for (int i = 0; i < InventoryData.Num(); ++i)
			{
				if (InventoryData[i].Item_Image == NULL)
				{
					InventoryData[i] = NewItemInfo;

					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < InventoryData.Num(); ++i)
		{
			if (InventoryData[i].Item_Image == NULL)
			{
				InventoryData[i] = NewItemInfo;

				break;
			}
		}
	}

	ReflashSlot();
}

void UHT_InventoryWidget::SetPos(FVector2D vPos)
{
	this->SetPositionInViewport(vPos, false);
}

UHT_InventoryWidget::UHT_InventoryWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

FReply UHT_InventoryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

void UHT_InventoryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& InOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, InOperation);

	UHT_InventoryDragDropOperation* DragDropOp = NewObject<UHT_InventoryDragDropOperation>(UHT_InventoryDragDropOperation::StaticClass());

	DragDropOp->Pivot = EDragPivot::MouseDown;

	UUserWidget* pWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryMoveWidget);

	this->SetVisibility(ESlateVisibility::Collapsed);

	if (DragDropOp)
	{
		DragDropOp->Payload = pWidget;
		DragDropOp->DefaultDragVisual = pWidget;
		DragDropOp->DragOffSet = MouseOffSet;
		DragDropOp->DragType = E_ITEM_DROP_TYPE::ITEM_DROP_INVENTORY;

		InOperation = DragDropOp;
	}
}