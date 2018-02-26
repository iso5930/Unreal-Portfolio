// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_PlayerExpWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_PlayerExpWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float ExpPersent;
	
public:
	class UHT_GameInstance* GameInstance;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};