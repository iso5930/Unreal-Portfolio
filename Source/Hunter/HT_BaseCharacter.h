// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "HT_BaseCharacter.generated.h"

UCLASS()
class HUNTER_API AHT_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* UserNameWidget;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AHT_BaseWeapon> TestWeaponClass;

private:
	TArray<class AHT_DropItem*> DropItemArr;

	class AHT_BaseNPC* OverlapNPC;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName WeaponAttachPointName;

	UPROPERTY(BlueprintReadOnly)
	class AHT_BaseWeapon* Weapon;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsWeaponChange = false;
	
public:
	// Sets default values for this character's properties
	AHT_BaseCharacter();

public:
	void MoveForward(float Value);
	void MoveRight(float Value);

public:
	void OnInventoryWidget();
	void Test();
	void Action_ItemTake();

	void OnInputTextWidget();

public:
	void OnTestFunction();

public:
	FName GetWeaponAttachPointName() const;

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappingComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};