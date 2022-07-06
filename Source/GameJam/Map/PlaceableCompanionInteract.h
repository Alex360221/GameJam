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
		class ABaseAICompanion* companion;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float companionActivateDistance = 500;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector companionTargetPoint;

	bool CompanionWithinRange(FVector target, float distance);

};