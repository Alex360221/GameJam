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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool stopFire = true;
	bool stopInput = false;

	void MoveForward(float axis) { if (!stopInput) { AddMovementInput(GetActorForwardVector(), axis); } }
	void MoveRight(float axis) { if (!stopInput) { AddMovementInput(GetActorRightVector(), axis); } }

	void TurnAtRate(float axis) { if (!stopInput) { ABaseCharacter::AddControllerYawInput(axis); } }
	void LookUpRate(float axis) { if (!stopInput) { ABaseCharacter::AddControllerPitchInput(axis); } }

	void StartJump() { if (!stopInput) { ABaseCharacter::Jump(); } }
	void EndJump() { if (!stopInput) { ABaseCharacter::StopJumping(); } }

	
private:

	bool fireDown = false;
	float fireLastCounter = 0;
	void FireDown() { if (!stopFire) { fireDown = true; } }
	void FireUp() { if (!stopFire) { fireDown = false; } }
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float fireCounterLimit = 1.f;

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

	//add Item to inventory
	UFUNCTION(BlueprintCallable)
		//Adds item to inventory
		void AddItemToInventory(class ABaseItemClass* item);
	//will pick up item
	void PickUpUtem();
	UFUNCTION(BlueprintCallable)
		bool PlayerHasItem(FString itemName);

private:

	

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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float damageAmount = 30.f;

	void InteractWithObject();
	
private:
	//stat fucntions
	void Regen();

};
