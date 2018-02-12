// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "HT_StagePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class HUNTER_API AHT_StagePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int ClientPlayerNum;
	
public:
	UFUNCTION(Client, Reliable)
	void ClientSetPlayerNum(int Num);

	void ClientSetPlayerNum_Implementation(int Num);
};