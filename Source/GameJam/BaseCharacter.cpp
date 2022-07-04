// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Items/BaseItemClass.h"

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


}

void ABaseCharacter::PickUpUtem()
{
	bool isHit = false;
	FHitResult hit = LineTraceCamera(&isHit);
	if (isHit)
	{
		ABaseItemClass* item = Cast<ABaseItemClass>(hit.GetActor());
		if (item)
		{
			GLog->Log("Item Hit");
		}
		else { GLog->Log("No Item"); }
	}
}

FHitResult ABaseCharacter::LineTraceCamera(bool* isHit)
{
	GLog->Log("Line Trace add");
	APlayerCameraManager* playerCameraManger = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector start = playerCameraManger->GetCameraLocation();
	FVector forwardVector = playerCameraManger->GetActorForwardVector();
	FVector end = (forwardVector * 400) + start;
	FCollisionQueryParams collisionsParms;
	FHitResult outHit;
	bool hit = GetWorld()->LineTraceSingleByChannel(outHit, start, end, ECC_Visibility, collisionsParms);
	isHit = &hit;
	return outHit;
}

