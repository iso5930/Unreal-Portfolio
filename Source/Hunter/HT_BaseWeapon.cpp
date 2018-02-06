// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseWeapon.h"
#include "HT_BaseCharacter.h"
#include "HT_GameInstance.h"

// Sets default values
AHT_BaseWeapon::AHT_BaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

bool AHT_BaseWeapon::SetWeaponIndex(int32 Index)
{
	WeaponIndex = Index - 7;

	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	WeaponMesh->SetSkeletalMesh(GameInstance->WeaponMeshs[WeaponIndex]);

	return true;
}

void AHT_BaseWeapon::SetWeaponType(E_WEAPON_TYPE NewType)
{
	WeaponType = NewType;
}

void AHT_BaseWeapon::AttachMeshToPawn(FName AttachName)
{
	if (OwnerCharacter != NULL)
	{
		USkeletalMeshComponent* PawnMesh = OwnerCharacter->GetMesh();
		
		WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), AttachName);
	}
}

E_WEAPON_TYPE AHT_BaseWeapon::GetWeaponType()
{
	return WeaponType;
}

void AHT_BaseWeapon::SetNextAttack(bool NextAttack)
{
	IsNextAttack = NextAttack;
}

// Called when the game starts or when spawned
void AHT_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AHT_BaseWeapon::Attack()
{
	E_PLAYER_STATE PlayerState = OwnerCharacter->GetPlayerState();

	if (PlayerState == E_PLAYER_STATE::PLAYER_STATE_IDLE)
	{
		IsNextAttack = false;

		OwnerCharacter->SetPlayerState(E_PLAYER_STATE::PLAYER_STATE_ATTACK01);

		if (Attack01_Montage != NULL)
		{
			OwnerCharacter->PlayAnimMontage(Attack01_Montage);
		}


		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Attack 01"));
	}
	else if (PlayerState == E_PLAYER_STATE::PLAYER_STATE_ATTACK01 && IsNextAttack)
	{
		IsNextAttack = false;

		OwnerCharacter->SetPlayerState(E_PLAYER_STATE::PLAYER_STATE_ATTACK02);

		if (Attack02_Montage != NULL)
		{
			OwnerCharacter->PlayAnimMontage(Attack02_Montage);
		}


		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Attack 02"));
	}
	else if (PlayerState == E_PLAYER_STATE::PLAYER_STATE_ATTACK02 && IsNextAttack)
	{
		IsNextAttack = false;

		OwnerCharacter->SetPlayerState(E_PLAYER_STATE::PLAYER_STATE_ATTACK03);

		if (Attack03_Montage != NULL)
		{
			OwnerCharacter->PlayAnimMontage(Attack03_Montage);
		}

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Attack 03"));
	}
	else if (PlayerState == E_PLAYER_STATE::PLAYER_STATE_ATTACK03 && IsNextAttack)
	{
		IsNextAttack = false;

		OwnerCharacter->SetPlayerState(E_PLAYER_STATE::PLAYER_STATE_ATTACK04);

		if (Attack04_Montage != NULL)
		{
			OwnerCharacter->PlayAnimMontage(Attack04_Montage);
		}

		UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("Attack 04"));
	}
}

// Called every frame
void AHT_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}