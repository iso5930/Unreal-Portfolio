// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_DamegeEffect.generated.h"

UCLASS()
class HUNTER_API AHT_DamegeEffect : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float Damege;
	
public:	
	// Sets default values for this actor's properties
	AHT_DamegeEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};