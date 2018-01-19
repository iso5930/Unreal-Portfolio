// Fill out your copyright notice in the Description page of Project Settings.

#include "Hunter.h"
#include "HT_BaseWeapon.h"


// Sets default values
AHT_BaseWeapon::AHT_BaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AHT_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AHT_BaseWeapon::Attack()
{

}

// Called every frame
void AHT_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}