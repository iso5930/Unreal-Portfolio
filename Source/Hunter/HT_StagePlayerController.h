// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "HT_StagePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_StagePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> StageWidget;

private:
	int PlayerNum;

public:
	UFUNCTION(NetMulticast, Reliable)
	void SetPlayerNum(int Num);

	void SetPlayerNum_Implementation(int Num);

public:
	virtual void BeginPlay() override;
};