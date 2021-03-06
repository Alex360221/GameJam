// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableInteract.generated.h"

UCLASS()
class GAMEJAM_API APlaceableInteract : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UStaticMeshComponent* objectMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString requiredItem;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ABaseCharacter* player;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool hideAfterInteract = true;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USoundBase* sound;

	void InteractWithObject(class ABaseCharacter* newPlayer);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool callInteractFucntion = false;
private:
	void RemoveWall();

};
