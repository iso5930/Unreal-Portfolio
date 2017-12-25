// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HT_LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_LobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UUserWidget> CharacterSelectWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WidgetClass")
	TSubclassOf<class UUserWidget> CharacterSlotWidgetClass;

protected:
	virtual void BeginPlay() override;
};