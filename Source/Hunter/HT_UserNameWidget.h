// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_UserNameWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_UserNameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserName;
};