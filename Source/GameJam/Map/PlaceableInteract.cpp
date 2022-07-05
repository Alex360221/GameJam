// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableInteract.h"
#include "Components/StaticMeshComponent.h"
#include <GameJam/BaseCharacter.h>

// Sets default values
APlaceableInteract::APlaceableInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	objectMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	requiredItem = "Enter Item";
}

// Called when the game starts or when spawned
void APlaceableInteract::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaceableInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlaceableInteract::InteractWithObject(class ABaseCharacter* newPlayer)
{
	player = newPlayer;
	if (player)
	{
		if (player->PlayerHasItem(requiredItem))
		{
			GLog->Log("Can interact");
			RemoveWall();
			callInteractFucntion = true;
		}
		else { GLog->Log("Doesn't have item"); }
	}
}

void APlaceableInteract::RemoveWall()
{
	if (player)
	{
		objectMesh->SetHiddenInGame(true);
		objectMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


