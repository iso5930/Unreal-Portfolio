// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_BaseWeapon.generated.h"

UENUM(BlueprintType)
enum class E_WEAPON_TYPE : uint8
{
	WEAPON_SCYTHE UMETA(DisplayName = "WEAPON_SCYTHE"),
	WEAPON_DUAL_BLADE UMETA(DisplayName = "WEAPON_DUAL_BLADE")
};

UCLASS()
class HUNTER_API AHT_BaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent * WeaponMesh;

public:
	E_WEAPON_TYPE WeaponType;
	class AHT_BaseCharacter* OwnerCharacter;
	
public:	
	// Sets default values for this actor's properties
	AHT_BaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Attack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};