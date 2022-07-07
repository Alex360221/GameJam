// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "BaseProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Items/BaseItemClass.h"
#include "Map/PlaceableInteract.h"
#include "AI/BaseAICompanion.h"
#include "AI/BaseAIEnemy.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));

	maxHealth = 100;
	currentHealth = 50;
	currentStatTimer = 0;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IsPlayingLookingAtItem();
	currentStatTimer += DeltaTime;
	if (currentStatTimer > 0.1)
	{
		currentStatTimer = 0;
		Regen();
	}

	fireLastCounter += DeltaTime;
	if (fireDown)
	{
		if (fireLastCounter >= fireCounterLimit)
		{
			fireLastCounter = 0;
			Fire();
		}
	}

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Player Movement
	PlayerInputComponent->BindAxis("MoveX", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveY", this, &ABaseCharacter::MoveRight);

	// Player Look Movement
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::LookUpRate);

	//Jump input

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABaseCharacter::EndJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABaseCharacter::FireDown);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABaseCharacter::FireUp);

	PlayerInputComponent->BindAction("PickUpItem", IE_Pressed, this, &ABaseCharacter::PickUpUtem);
	PlayerInputComponent->BindAction("InteractWithObject", IE_Pressed, this, &ABaseCharacter::InteractWithObject);


}

void ABaseCharacter::Fire()
{
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		//MuzzleOffset.Set(30.0f, 0.0f, 0.0f);


		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			ABaseProjectile* Projectile = World->SpawnActor<ABaseProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				APlayerCameraManager* playerCameraManger = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
				// Set the projectile's initial trajectory.
				//FVector LaunchDirection = MuzzleRotation.Vector();
				FVector LaunchDirection = playerCameraManger->GetActorForwardVector();
				Projectile->FireInDirection(LaunchDirection,this);

				//Do line trace to see if it will hit anything
				
				FVector start = playerCameraManger->GetCameraLocation();
				FVector forwardVector = playerCameraManger->GetActorForwardVector();
				FVector end = (forwardVector * 3000) + start;
				FCollisionQueryParams collisionsParms;
				if (Projectile) { collisionsParms.AddIgnoredActor(Projectile->GetUniqueID()); }
				FHitResult hit;
				GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility, collisionsParms);
				
				if (hit.bBlockingHit)
				{
					GLog->Log("Hit Something " + hit.Actor->GetName());
					ABaseAIEnemy* enemy = Cast<ABaseAIEnemy>(hit.Actor);
					if (enemy)
					{
						GLog->Log("Hit Enemy!!!!!!!!!!!");
						enemy->DamageEnemy(damageAmount);
						//enemy->Destroy();
					}
				}
			}
		}
	}
}

void ABaseCharacter::ReSpawn(FVector respawnPoint, FVector respawnDir)
{
	currentHealth = maxHealth;

	if (companion)
	{
		if (companion->followPlayer)
		{
			FVector point = (respawnDir * 100) + respawnPoint;
			companion->SetActorLocation(point);
			companion->targetLocation = point;
		}
	}
}

void ABaseCharacter::PickUpUtem()
{
	FHitResult hit = LineTraceCamera(nullptr, 400);
	if (hit.bBlockingHit)
	{
		ABaseItemClass* item = Cast<ABaseItemClass>(hit.GetActor());
		if (item)
		{
			GLog->Log("Item Hit");
			AddItemToInventory(item);
		}
		else { GLog->Log("No Item"); }
	}
}

void ABaseCharacter::AddItemToInventory(ABaseItemClass* item)
{
	//Adds item to inventory
	inventory.Add(item);
	item->SetActorEnableCollision(false);
	item->SetActorHiddenInGame(true);
	GLog->Log("Item Added");
}

bool ABaseCharacter::PlayerHasItem(FString itemName)
{
	for (int i = 0; i < inventory.Num(); i++)
	{
		if (inventory[i]->itemName == itemName) { return true; }
	}
	return false;
}

FHitResult ABaseCharacter::LineTraceCamera(AActor* ingoreActor, float lineLength)
{
	//GLog->Log("Line Trace add");
	APlayerCameraManager* playerCameraManger = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector start = playerCameraManger->GetCameraLocation();
	FVector forwardVector = playerCameraManger->GetActorForwardVector();
	FVector end = (forwardVector * lineLength) + start;
	FCollisionQueryParams collisionsParms;
	if (ingoreActor) { collisionsParms.AddIgnoredActor(ingoreActor->GetUniqueID()); }
	FHitResult outHit;
	bool hit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionsParms);
	return outHit;
}

void ABaseCharacter::IsPlayingLookingAtItem()
{
	FHitResult hit = LineTraceCamera(nullptr, 400);
	if (hit.bBlockingHit)
	{
		ABaseItemClass* item = Cast<ABaseItemClass>(hit.GetActor());
		if (item)
		{
			GLog->Log("Looking at Item");
			displayItemPickUp = true;
			lookedAtItem = item;

			displayObjectInteract = false;
			lookAtObject = nullptr;
			return;
		}
		else
		{
			
			APlaceableInteract* object = Cast<APlaceableInteract>(hit.GetActor());
			if (object)
			{
				GLog->Log("Looking at Object");
				displayObjectInteract = true;
				lookAtObject = object;
				object->player = this;

				displayItemPickUp = false;
				lookedAtItem = nullptr;

				return;
			}
		}
	}

	displayItemPickUp = false;
	lookedAtItem = nullptr;
	displayObjectInteract = false;
	lookAtObject = nullptr;
}

void ABaseCharacter::InteractWithObject()
{
	FHitResult hit = LineTraceCamera(nullptr, 400);
	if (hit.bBlockingHit)
	{
		APlaceableInteract* object = Cast<APlaceableInteract>(hit.GetActor());
		if (object)
		{
			GLog->Log("Item Hit");
			object->InteractWithObject(this);
		}
		else { GLog->Log("No Item"); }
	}
}

void ABaseCharacter::Regen()
{
	if (currentHealth + 0.2 <= maxHealth)
	{
		currentHealth += 0.2;
	}
	else
	{
		currentHealth = maxHealth;
	}
}




