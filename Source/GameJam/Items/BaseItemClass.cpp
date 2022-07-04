// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItemClass.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseItemClass::ABaseItemClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	itemName = "Base Item";

}

// Called when the game starts or when spawned
void ABaseItemClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItemClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

