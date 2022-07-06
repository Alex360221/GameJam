// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAICharacter.h"
#include "BaseAICompanion.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API ABaseAICompanion : public ABaseAICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseAICompanion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool followPlayer = false;
	bool companionInteractSet = false;

private:
	bool moveToPlayer = false;
	bool shouldMove = false;

	bool ShouldStartMove();
	bool ShouldStopMove();	
};
