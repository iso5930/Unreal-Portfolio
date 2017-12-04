// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_LoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	bool IsLoginChaking = false;

public:
	UFUNCTION(BlueprintCallable)
	void OnLoginButton();

	UFUNCTION(BlueprintCallable)
	void OnCencelButton();

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};