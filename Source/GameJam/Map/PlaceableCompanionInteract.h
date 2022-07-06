// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableCompanionInteract.generated.h"

UCLASS()
class GAMEJAM_API APlaceableCompanionInteract : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableCompanionInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UStaticMeshComponent* objectMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ABaseCharacter* character;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ABaseAICompanion* companion;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float companionActivateDistance = 500;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector companionTargetPoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector companionShootTargetPoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector playerStopPoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float playerStopDistance = 300.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector playerLookAtPoint;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool toggleOn = false;

	bool CompanionWithinRange(FVector target, float distance);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int shots = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float timeBetweenShots = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float destroyDelay = 1.f;

private:
	bool hasCalledShooting = false;
	bool shooting = false;
	
	int shotCount = 0;
	float shotTimer = 0.f;
	bool doneInteract = false;
	float doneInteractTimer = 0.f;
};
