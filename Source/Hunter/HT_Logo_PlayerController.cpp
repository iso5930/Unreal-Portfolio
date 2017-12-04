// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_Logo_PlayerController.h"
#include "Blueprint/UserWidget.h"

void AHT_Logo_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (LogoWidget != NULL)
	{
		UUserWidget* pLogoWidget = CreateWidget<UUserWidget>(GetWorld(), LogoWidget);

		if (pLogoWidget != NULL)
		{
			pLogoWidget->AddToViewport();

			APlayerController* MyController = GetWorld()->GetFirstPlayerController();

			if (MyController != NULL)
			{
				MyController->bShowMouseCursor = true;
				MyController->bEnableClickEvents = true;
			}
		}
	}
}