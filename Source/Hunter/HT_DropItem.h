// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_DropItem.generated.h"

UENUM(BlueprintType)
enum class E_ITEM_TYPE : uint8
{
	ITEM_TYPE_NONE UMETA(DisplayName = "ITEM_TYPE_NONE"), //기타 아이템, 일명 잡템
	ITEM_TYPE_WEAPON_SCYTHE UMETA(DisplayName = "ITEM_TYPE_WEAPON_SCYTHE"), //캐릭터가 장착할 수 있는 무기
	ITEM_TYPE_WEAPON_DUAL_BLADE UMETA(DisplayName = "ITEM_TYPE_WEAPON_DUAL_BLADE"),
	ITEM_TYPE_EQUIP UMETA(DisplayName = "ITEM_TYPE_EQUIP"), //캐릭터가 장착할 수 있는 방어구
	ITEM_TYPE_POTION UMETA(DisplayName = "ITEM_TYPE_POTION") //포션
};

USTRUCT(BlueprintType)
struct FItem_Info
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Item_Image; //인벤토리에 보일 이미지.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Item_Name; //아이템의 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Item_Num; //아이템 고유 번호.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Item_Cnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Item_MaxCnt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	E_ITEM_TYPE Item_Type = E_ITEM_TYPE::ITEM_TYPE_NONE;

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
