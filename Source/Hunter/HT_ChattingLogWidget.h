// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_ChattingLogWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_ChattingLogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};