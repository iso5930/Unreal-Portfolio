// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HT_Logo_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_Logo_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UserWidgets")
	TSubclassOf<class UUserWidget> LogoWidget;

public:
	virtual void BeginPlay() override;
};