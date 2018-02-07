// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseMonster.h"
#include "HT_MonsterAIController.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

// Sets default values
AHT_BaseMonster::AHT_BaseMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationYaw = true;

	AIControllerClass = AHT_MonsterAIController::StaticClass();

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SensingInterval = 0.25f;

	PawnSensing->OnSeePawn.AddDynamic(this, &AHT_BaseMonster::OnSeePlayer);

	MonsterState = E_MONSTER_STATE::MONSTER_STATE_IDLE;
}

void AHT_BaseMonster::OnSeePlayer(APawn* InPawn)
{
	UE_LOG(LogClass, Warning, TEXT("%s %d"), TEXT("플레이어 감지!"));
}

E_MONSTER_STATE AHT_BaseMonster::GetMonsterState()
{
	return MonsterState;
}

void AHT_BaseMonster::SetMonsterState(E_MONSTER_STATE NewState)
{
	MonsterState = NewState;
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