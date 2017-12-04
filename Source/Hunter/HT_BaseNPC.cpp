// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseNPC.h"
#include "HT_GameInstance.h"
#include "UserWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "HT_ButtonWidget.h"
#include "HT_StoreButtonWidget.h"

// Sets default values
AHT_BaseNPC::AHT_BaseNPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}

void AHT_BaseNPC::NPCMenuWidgetPopup()
{
	UHT_GameInstance* GameInstance = Cast<UHT_GameInstance>(GetWorld()->GetGameInstance());
	
	GameInstance->NPCMenuWidget = CreateWidget<UUserWidget>(GetWorld(), GameInstance->NPCMenuWidgetClass);
	GameInstance->NPCMenuWidget->AddToViewport();

	UUniformGridPanel* ButtonLayout = Cast<UUniformGridPanel>(GameInstance->NPCMenuWidget->GetWidgetFromName("ButtonLayout"));

	for (int i = 0; i < ButtonClassArray.Num(); ++i)
	{
		UUserWidget* ButtonWidget = CreateWidget<UUserWidget>(GetWorld(), ButtonClassArray[i]);

		ButtonLayout->AddChild(ButtonWidget);

		UUniformGridSlot* Slot = Cast<UUniformGridSlot>(ButtonWidget->Slot);

		Slot->SetColumn(i);

		Cast<UHT_ButtonWidget>(ButtonWidget)->SetOwnerWidget(GameInstance->NPCMenuWidget);
		Cast<UHT_ButtonWidget>(ButtonWidget)->SetOwnerNPC(this);
	}

	FInputModeUIOnly InputMode;

	InputMode = InputMode.SetWidgetToFocus(GameInstance->NPCMenuWidget->GetCachedWidget());

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController != NULL)
	{
		PlayerController->SetInputMode(InputMode);
	}

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
}

// Called when the game starts or when spawned
void AHT_BaseNPC::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHT_BaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}