// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseMonster.h"
#include "HT_MonsterAIController.h"

// Sets default values
AHT_BaseMonster::AHT_BaseMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationYaw = true;

	AIControllerClass = AHT_MonsterAIController::StaticClass();
}

void AHT_BaseMonster::FaceRotation(FRotator NewControlRotation, float DeltaTime /*= 0.f*/)
{
	FRotator CurrentRot = FMath::RInterpTo(GetActorRotation(), NewControlRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRot, DeltaTime);
}

// Called when the game starts or when spawned
void AHT_BaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHT_BaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}