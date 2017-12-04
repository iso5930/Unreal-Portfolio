// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_ButtonWidget.h"

void UHT_ButtonWidget::SetOwnerWidget(UUserWidget* Owner)
{
	OwnerWidget = Owner;
}

void UHT_ButtonWidget::SetOwnerNPC(AHT_BaseNPC* Owner)
{
	OwnerNPC = Owner;
}

void UHT_ButtonWidget::Button_Use()
{

}