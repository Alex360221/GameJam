// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICompanion.h"

// Sets default values
ABaseAICompanion::ABaseAICompanion()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	targetLocation = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void ABaseAICompanion::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseAICompanion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!moveToPlayer)
	{
		if (ShouldStartMove())
		{
			moveToPlayer = true;
		}
	}
	else
	{
		if(!ShouldStopMove()) { FollowPlayer(); }	
		else { moveToPlayer = false; }
	}
}

bool ABaseAICompanion::ShouldStartMove()
{
	if (DisToPlayer() > 300)
	{
		return true;
	}
	return false;
}

bool ABaseAICompanion::ShouldStopMove()
{
	if (DisToPlayer() < 100)
	{
		return true;
	}
	return false;
}

