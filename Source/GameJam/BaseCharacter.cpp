// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Items/BaseItemClass.h"
#include "Map/PlaceableInteract.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	playerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Player Mesh"));


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

	PlayerInputComponent->BindAction("PickUpItem", IE_Pressed, this, &ABaseCharacter::PickUpUtem);
	PlayerInputComponent->BindAction("InteractWithObject", IE_Pressed, this, &ABaseCharacter::InteractWithObject);


}

void ABaseCharacter::PickUpUtem()
{
	FHitResult hit = LineTraceCamera();
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

FHitResult ABaseCharacter::LineTraceCamera()
{
	//GLog->Log("Line Trace add");
	APlayerCameraManager* playerCameraManger = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector start = playerCameraManger->GetCameraLocation();
	FVector forwardVector = playerCameraManger->GetActorForwardVector();
	FVector end = (forwardVector * 400) + start;
	FCollisionQueryParams collisionsParms;
	FHitResult outHit;
	bool hit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionsParms);
	return outHit;
}

void ABaseCharacter::IsPlayingLookingAtItem()
{
	FHitResult hit = LineTraceCamera();
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
			GLog->Log("Looking at Object");
			APlaceableInteract* object = Cast<APlaceableInteract>(hit.GetActor());
			if (object)
			{
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
	FHitResult hit = LineTraceCamera();
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




