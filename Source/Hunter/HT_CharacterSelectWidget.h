// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_CharacterSelectWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_CharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CreateCharacter();

	UFUNCTION(BlueprintCallable)
	void DeleteCharacter();
};