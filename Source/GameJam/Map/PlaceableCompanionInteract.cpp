// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableCompanionInteract.h"
#include "Components/StaticMeshComponent.h"
#include <GameJam/AI/BaseAICompanion.h>

// Sets default values
APlaceableCompanionInteract::APlaceableCompanionInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));

}

// Called when the game starts or when spawned
void APlaceableCompanionInteract::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlaceableCompanionInteract::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!companion) { return; }
	if (CompanionWithinRange(GetActorLocation(), companionActivateDistance))
	{	
		if (CompanionWithinRange(companionTargetPoint, 50))
		{
			GLog->Log("Companion At Target Point");
		}
		else 
		{
			companion->targetLocation = companionTargetPoint;
		}
	}

}

bool APlaceableCompanionInteract::CompanionWithinRange(FVector target, float distance)
{
	if (companion)
	{
		if (FVector::Distance(target, companion->GetActorLocation()) <= distance)
		{
			return true;
		}
	}
	return false;
}

