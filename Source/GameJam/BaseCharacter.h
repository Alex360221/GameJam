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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ABaseAICompanion* companion;

	void MoveForward(float axis) { AddMovementInput(GetActorForwardVector(), axis); }
	void MoveRight(float axis) { AddMovementInput(GetActorRightVector(), axis); }

	void TurnAtRate(float axis) { ABaseCharacter::AddControllerYawInput(axis); }
	void LookUpRate(float axis) { ABaseCharacter::AddControllerPitchInput(axis); }

	void StartJump() { ABaseCharacter::Jump(); }
	void EndJump() { ABaseCharacter::StopJumping(); }

	// Function that handles firing projectiles.
	UFUNCTION()
		void Fire();
	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABaseProjectile> ProjectileClass;

	//player stats
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float currentHealth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float maxHealth;
private:
	float currentStatTimer;

public:

	UFUNCTION(BlueprintCallable)
		void ReSpawn(FVector respawnPoint, FVector respawnDir);

//inventory
	TArray<class ABaseItemClass*> inventory;

	//will pick up item
	void PickUpUtem();
	UFUNCTION(BlueprintCallable)
		bool PlayerHasItem(FString itemName);

private:

	//Adds item to inventory
	void AddItemToInventory(class ABaseItemClass* item);

	FHitResult LineTraceCamera(AActor* ingoreActor, float lineLength);

	//will dertimne if the player is looking at an item
	void IsPlayingLookingAtItem();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool displayItemPickUp = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ABaseItemClass* lookedAtItem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool displayObjectInteract = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class APlaceableInteract* lookAtObject;


	void InteractWithObject();
	
private:
	//stat fucntions
	void Regen();

};
