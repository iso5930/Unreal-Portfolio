// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_CharacterSlotWidget.generated.h"

USTRUCT(BlueprintType)
struct FCharacter_Info
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int Level;
};

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_CharacterSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FCharacter_Info CharacterInfo;

public:
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void SetSlot(FCharacter_Info Info);
protected:
	virtual void NativeConstruct() override;
};