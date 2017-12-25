// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_LobbyPlayerController.h"
#include "HT_GameInstance.h"
#include <UserWidget.h>
#include <ScrollBox.h>
#include "HT_CharacterSlotWidget.h"

void AHT_LobbyPlayerController::BeginPlay()
{
	//게임 인스턴스에 위젯이 안 만들어져 있다면.. Select 위젯 생성.

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
					}
				}
			}
		}
	}	
}