// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_DamegeEffect.h"


// Sets default values
AHT_DamegeEffect::AHT_DamegeEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damege = 0.0f;
}

// Called when the game starts or when spawned
void AHT_DamegeEffect::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHT_DamegeEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}