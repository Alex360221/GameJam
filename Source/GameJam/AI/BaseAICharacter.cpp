// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICharacter.h"
#include <GameJam/BaseCharacter.h>

// Sets default values
ABaseAICharacter::ABaseAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	targetLocation = FVector(0, 0, 0);
}

// Called when the game starts or when spawned
void ABaseAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseAICharacter::CalculateTargetLocation()
{

}

void ABaseAICharacter::FollowPlayer()
{
	if (player)
	{
		targetLocation = player->GetActorLocation();
	}
}

float ABaseAICharacter::DisToPlayer()
{
	if (player)
	{
		return FVector::Dist(GetActorLocation(), player->GetActorLocation());
	}
	return 0.0f;
}

