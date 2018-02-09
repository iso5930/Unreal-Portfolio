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
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent * WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* WeaponCollision;

public:
	E_WEAPON_TYPE WeaponType;
	class AHT_BaseCharacter* OwnerCharacter;

protected:
	UAnimMontage* Attack01_Montage;
	UAnimMontage* Attack02_Montage;
	UAnimMontage* Attack03_Montage;
	UAnimMontage* Attack04_Montage;

protected:
	int32 WeaponIndex;
	bool IsNextAttack;
	
public:	
	// Sets default values for this actor's properties
	AHT_BaseWeapon();

public:
	bool SetWeaponIndex(int32 Index);
	void SetWeaponType(E_WEAPON_TYPE NewType);

public:
	void AttachMeshToPawn(FName AttachName);

public:
	UFUNCTION(BlueprintCallable)
	E_WEAPON_TYPE GetWeaponType();

	UFUNCTION(BlueprintCallable)
	void SetNextAttack(bool NextAttack);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Attack();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};