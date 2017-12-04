// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_DropItem.h"
#include "HT_BaseNPC.generated.h"

UCLASS()
class HUNTER_API AHT_BaseNPC : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCMenuWidget")
	TArray<TSubclassOf<class UUserWidget>> ButtonClassArray;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCStore")
	TArray<int> StoreItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCStore")
	bool IsStore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPCStore")
	FString StoreName;
		
public:	
	// Sets default values for this actor's properties
	AHT_BaseNPC();

public:
	void NPCMenuWidgetPopup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};