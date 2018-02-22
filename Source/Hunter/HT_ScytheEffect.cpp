// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_ScytheEffect.h"

// Sets default values
AHT_ScytheEffect::AHT_ScytheEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AccTime = 0.0f;
}

// Called when the game starts or when spawned
void AHT_ScytheEffect::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHT_ScytheEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccTime += DeltaTime;

	if (AccTime >= LifeTime)
	{
		EffectPSC->DeactivateSystem();

		Destroy();
	}
}

void AHT_ScytheEffect::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	if (EffectFX != NULL)
	{
		FVector4 vPos = GetActorLocation();

		EffectPSC = UGameplayStatics::SpawnEmitterAtLocation(this, EffectFX, GetActorLocation(), GetActorRotation());
	}

	if (EffectSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, EffectSound, GetActorLocation());
	}
}