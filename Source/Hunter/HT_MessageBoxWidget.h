// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_MessageBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_MessageBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool IsLogin = false;
	
protected:
	UPROPERTY(BlueprintReadWrite)
	FString	MessageText;

public:
	UFUNCTION(BlueprintCallable, Category = "MessageWidget")
	void SetMessageText(FString NewText);
};