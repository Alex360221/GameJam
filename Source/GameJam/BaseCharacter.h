// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GAMEJAM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UStaticMeshComponent* playerMesh;

	void MoveForward(float axis) { AddMovementInput(GetActorForwardVector(), axis); }
	void MoveRight(float axis) { AddMovementInput(GetActorRightVector(), axis); }

	void TurnAtRate(float axis) { ABaseCharacter::AddControllerYawInput(axis); }
	void LookUpRate(float axis) { ABaseCharacter::AddControllerPitchInput(axis); }

	void StartJump() { ABaseCharacter::Jump(); }
	void EndJump() { ABaseCharacter::StopJumping(); }


//inventory
	TArray<class ABaseItemClass*> inventory;

};
