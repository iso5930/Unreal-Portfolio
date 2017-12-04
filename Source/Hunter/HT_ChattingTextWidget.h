// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_ChattingTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_ChattingTextWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	FString	ChattingText;

public:
	void Init_ChattingText(FString NewText);
};