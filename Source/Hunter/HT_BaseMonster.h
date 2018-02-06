// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "HT_BaseMonster.generated.h"

UCLASS()
class HUNTER_API AHT_BaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

public:
	// Sets default values for this pawn's properties
	AHT_BaseMonster();

public:
	virtual void FaceRotation(FRotator NewControlRotation, float DeltaTime = 0.f) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};