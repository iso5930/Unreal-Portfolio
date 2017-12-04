// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_DropItem.h"
#include "HT_GameInstance.h"

void AHT_DropItem::AddItem(int32 ItemIndex)
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());

	if (GameInstance != NULL)
	{
		FItem_Info NewItem;

		NewItem = GameInstance->Item_DataBase[ItemIndex];
		NewItem.Item_Cnt = rand() % 10 + 1;

		ItemArray.Add(NewItem);
	}
}

// Sets default values
AHT_DropItem::AHT_DropItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollision);
	Mesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AHT_DropItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHT_DropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHT_DropItem::Destroyed()
{
	UE_LOG(LogClass, Warning, TEXT("%s"), TEXT("드랍 아이템 삭제"));
}