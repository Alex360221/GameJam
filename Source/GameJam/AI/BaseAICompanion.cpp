// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAICompanion.h"
#include <GameJam/BaseProjectile.h>
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseAICompanion::ABaseAICompanion()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	targetLocation = FVector(0, 0, 0);
	followPlayer = false;
}

// Called when the game starts or when spawned
void ABaseAICompanion::BeginPlay()
{
	Super::BeginPlay();
	targetLocation = GetActorLocation();

}

// Called every frame
void ABaseAICompanion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (followPlayer && !companionInteractSet)
	{
		if (!moveToPlayer)
		{
			if (ShouldStartMove())
			{
				moveToPlayer = true;
			}
		}
		else
		{
			if (!ShouldStopMove()) { FollowPlayer(50); }
			else { moveToPlayer = false; }
		}
	}
	else 
	{ 
		moveToPlayer = false; 
		//is too close to player if so move behind player

	}
}

bool ABaseAICompanion::ShouldStartMove()
{
	if (DisToPlayer() > 500)
	{
		GLog->Log("Start Moving");
		return true;
	}
	return false;
}

bool ABaseAICompanion::ShouldStopMove()
{
	if (DisToPlayer() < 100)
	{
		GLog->Log("Stop Moving");
		return true;
	}
	return false;
}

void ABaseAICompanion::FireAtTarget(FVector target)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target);
		FVector dir = target - GetActorLocation();
		dir.Normalize();
		// Spawn the projectile at the muzzle.
		ABaseProjectile* projectile = World->SpawnActor<ABaseProjectile>(ProjectileClass, GetActorLocation() + (dir * 30), 
			rotator, SpawnParams);
		if (projectile)
		{
			
			projectile->FireInDirection(dir, this);
		}
	}
}


