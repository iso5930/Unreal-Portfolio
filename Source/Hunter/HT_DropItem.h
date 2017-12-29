// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HT_DropItem.generated.h"

UENUM(BlueprintType)
enum class E_ITEM_TYPE : uint8
{
	ITEM_TYPE_NONE UMETA(DisplayName = "ITEM_TYPE_NONE"), //��Ÿ ������, �ϸ� ����
	ITEM_TYPE_WEAPON_SCYTHE UMETA(DisplayName = "ITEM_TYPE_WEAPON_SCYTHE"), //ĳ���Ͱ� ������ �� �ִ� ����
	ITEM_TYPE_WEAPON_DUAL_BLADE UMETA(DisplayName = "ITEM_TYPE_WEAPON_DUAL_BLADE"),
	ITEM_TYPE_EQUIP UMETA(DisplayName = "ITEM_TYPE_EQUIP"), //ĳ���Ͱ� ������ �� �ִ� ��
	ITEM_TYPE_POTION UMETA(DisplayName = "ITEM_TYPE_POTION") //����
};

USTRUCT(BlueprintType)
struct FItem_Info
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Item_Image; //�κ��丮�� ���� �̹���.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Item_Name; //�������� �̸�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Item_Num; //������ ���� ��ȣ.

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

//������ ���� �ٸ���� �ű��.

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
	TArray<FItem_Info> ItemArray; //����� �������� ������.

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
