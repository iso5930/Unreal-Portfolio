// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_PlayerStateWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_PlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float HpPersent;

	UPROPERTY(BlueprintReadWrite)
	FString HpString;

	class AHT_BaseCharacter* OwnerPlayer;

public:
	void SetOwnerPlayer(AHT_BaseCharacter* Player);
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};