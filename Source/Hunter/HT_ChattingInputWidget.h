// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HT_ChattingInputWidget.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API UHT_ChattingInputWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UUserWidget* InputWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> ChattingTextWidget;

public:
	UPROPERTY(BlueprintReadWrite)
	FString ChattingText;

public:
	UFUNCTION(BlueprintCallable, Category = "Chatting")
	bool OnTextChange(FString NewText);

	UFUNCTION(BlueprintCallable, Category = "Chatting")
	FString OnCommitted(FString InputText);

	virtual void NativeConstruct() override;
};