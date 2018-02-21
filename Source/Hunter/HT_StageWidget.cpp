// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StageWidget.h"
#include "HT_InventoryDragDropOperation.h"
#include "HT_GameInstance.h"
#include "HT_InventoryWidget.h"
#include "CanvasPanel.h"
#include "HT_StageWidget.h"
#include "HT_EquipInventory_Widget.h"
#include "HT_TakeItemWidget.h"

void UHT_StageWidget::PlayTakeItemAnim(FItem_Info Info)
{
	if (TakeItemAnim != NULL)
	{
		UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance != NULL)
		{
			PlayAnimation(TakeItemAnim);

			GameInstance->TakeItemWidget->TakeItem = Info;
		}
	}
}

bool UHT_StageWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UHT_InventoryDragDropOperation* DragDropOP = Cast<UHT_InventoryDragDropOperation>(InOperation);

	if (DragDropOP != NULL)
	{
		if (DragDropOP->DragType == E_ITEM_DROP_TYPE::ITEM_DROP_INVENTORY)
		{
			FVector2D vPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
			FVector2D Offset = DragDropOP->DragOffSet;

			vPos = vPos - Offset;

			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			if (GameInstance != NULL)
			{
				GameInstance->UserInventoryWidget->SetVisibility(ESlateVisibility::Visible);
				GameInstance->UserInventoryWidget->RemoveFromParent();
				GameInstance->UserInventoryWidget->AddToViewport();
				GameInstance->UserInventoryWidget->SetPos(vPos);
			}
		}
		else if (DragDropOP->DragType == E_ITEM_DROP_TYPE::ITEM_DROP_EQUIP)
		{
			FVector2D vPos = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
			FVector2D Offset = DragDropOP->DragOffSet;

			vPos = vPos - Offset;

			UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

			if (GameInstance != NULL)
			{
				GameInstance->EquipWidget->SetVisibility(ESlateVisibility::Visible);
				GameInstance->EquipWidget->RemoveFromParent();
				GameInstance->EquipWidget->AddToViewport();
				GameInstance->EquipWidget->SetPositionInViewport(vPos, false);
			}
		}
		else if(DragDropOP->DragType == E_ITEM_DROP_TYPE::ITEM_DROP_SLOT)
		{
			UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("¹ö¸®±â"));
		}
	}

	return true;
}