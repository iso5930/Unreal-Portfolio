// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_DropItem.generated.h"

USTRUCT(BlueprintType)
struct FItem_Info
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Item_Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Item_Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Item_Num;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Item_Cnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Item_MaxCnt;

	FItem_Info()
		:Item_Image(NULL), Item_Name(TEXT("None")), Item_Num(0), Item_Cnt(1), Item_MaxCnt(1)
	{

	}

	FItem_Info(UTexture2D* pImage, FString Name, int32 Num, int32 Cnt = 1, int32 MaxCnt = 1)
		:Item_Image(pImage), Item_Name(Name), Item_Num(Num), Item_Cnt(Cnt), Item_MaxCnt(MaxCnt)
	{

	}
};

//위쪽의 저거 다른대로 옮기기.

UCLASS()
class HUNTER_API AHT_DropItem : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

public:
	TArray<FItem_Info> ItemArray; //드랍된 아이템의 정보들.

public:
	void AddItem(int32 ItemIndex);
	
public:	
	// Sets default values for this actor's properties
	AHT_DropItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;
};
