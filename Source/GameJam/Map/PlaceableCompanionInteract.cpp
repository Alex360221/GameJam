// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableCompanionInteract.h"
#include "Components/StaticMeshComponent.h"
#include <GameJam/AI/BaseAICompanion.h>
#include <GameJam/BaseCharacter.h>
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlaceableCompanionInteract::APlaceableCompanionInteract()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));

	if (!sound)
	{
		sound = CreateDefaultSubobject<USoundBase>(TEXT("Sound"));

		static ConstructorHelpers::FObjectFinder<USoundBase>sounda(TEXT("SoundWave'/Game/Sounds/FloorBreaks.FloorBreaks'"));
		if (sounda.Succeeded())
		{
			sound = sounda.Object;
		}
	}

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

	if (toggleOn)
	{		
		if (!doneInteract)
		{
			if (character)
			{
				float playerDis = FVector::Distance(character->GetActorLocation(), playerStopPoint);
				if (playerDis <= playerStopDistance)
				{
					character->stopInput = true;
					FRotator rotator = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), playerLookAtPoint);
					character->GetController()->SetControlRotation(rotator);
				}
			}
			if (CompanionWithinRange(GetActorLocation(), companionActivateDistance))
			{
				GLog->Log("Companion Within range");
				if (CompanionWithinRange(companionTargetPoint, 50))
				{
					GLog->Log("Companion At Target Point");
					if (!hasCalledShooting)
					{
						GLog->Log("Start shooting");
						hasCalledShooting = true;
						shooting = true;				
						if (inCave) { UGameplayStatics::PlaySoundAtLocation(GetWorld(), sound, GetActorLocation(), 0.5f, 1.f, 0.f, nullptr, nullptr); }
						//companion->FireAtTarget(companionShootTargetPoint); 
					}
					else
					{
						if (shooting)
						{
							if (shotCount <= shots)
							{
								shotTimer += DeltaTime;
								if (shotTimer >= timeBetweenShots)
								{
									shotTimer = 0.f;
									shotCount++;
									GLog->Log("Fire Shot");
									companion->FireAtTarget(companionShootTargetPoint);
								}
							}
							else
							{
								shooting = false;
								doneInteract = true;
							}
						}
					}
				}
				else
				{
					companion->targetLocation = companionTargetPoint;
				}
			}
		}
		else
		{
			doneInteractTimer += DeltaTime;
			if (doneInteractTimer >= destroyDelay)
			{

				GLog->Log("Done inetracrtion!!!!!!!!");
				if (character) { character->stopInput = false; }
				Destroy();

			}
		}
	}
}

bool APlaceableCompanionInteract::CompanionWithinRange(FVector target, float distance)
{
	if (companion)
	{
		float dis = FVector2D::Distance(FVector2D(target), FVector2D(companion->GetActorLocation()));
		if (dis <= distance)
		{
			return true;
		}
	}
	return false;
}

