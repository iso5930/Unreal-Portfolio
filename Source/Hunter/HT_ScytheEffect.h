// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_ScytheEffect.generated.h"

UCLASS()
class HUNTER_API AHT_ScytheEffect : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* EffectFX;

	UParticleSystemComponent* EffectPSC;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	float LifeTime;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class USoundBase* EffectSound;

	float AccTime;
	
public:	
	// Sets default values for this actor's properties
	AHT_ScytheEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
};