// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_StoreSlotWidget.h"
#include "HT_GameInstance.h"
#include "HT_StoreTradeWidget.h"

void UHT_StoreSlotWidget::SetItemIndex(int Index)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	StoreItemIndex = Index;
	
	ItemName = GameInstance->Item_DataBase[Index].Item_Name;	
	ItemImage = GameInstance->Item_DataBase[Index].Item_Image;
}

int UHT_StoreSlotWidget::GetItemIndex()
{
	return StoreItemIndex;
}

FReply UHT_StoreSlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = FReply::Handled();

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	UHT_StoreTradeWidget* TradeWidget = CreateWidget<UHT_StoreTradeWidget>(GetWorld(), GameInstance->StoreTradeWidgetClass);
	
	FVector2D WidgetPos = InMouseEvent.GetScreenSpacePosition();

	TradeWidget->SetPositionInViewport(WidgetPos, false);
	TradeWidget->AddToViewport();
	TradeWidget->OwnerWidget = this;
	TradeWidget->IsBuy = true;
	TradeWidget->ButtonText = TEXT("±¸¸Å");

	return Reply;
}