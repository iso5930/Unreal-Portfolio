// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_ExitButtonWidget.h"

void UHT_ExitButtonWidget::Button_Use()
{
	if (OwnerWidget != NULL)
	{
		OwnerWidget->RemoveFromParent();

		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;

		FInputModeGameOnly InputMode;

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if (PlayerController != NULL)
		{
			PlayerController->SetInputMode(InputMode);
		}
	}
}