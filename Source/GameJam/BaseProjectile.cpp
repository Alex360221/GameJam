// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "AI/BaseAIEnemy.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    if (!RootComponent)
    {
        // Use a sphere as a simple collision representation.
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // Set the sphere's collision profile name to "Projectile".
        CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        // Event called when component hits something.
        CollisionComponent->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
        // Set the sphere's collision radius.
        CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        RootComponent = CollisionComponent;

        
        
    }

    if (!ProjectileMovementComponent)
    {
        // Use this component to drive this projectile's movement.
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = 3000.0f;
        ProjectileMovementComponent->MaxSpeed = 3000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
        

        
    }

    if (!ProjectileMeshComponent)
    {
        ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
        static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Player/Projectile.Projectile'"));
        if (Mesh.Succeeded())
        {
            ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
        }
    }

    static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Companion/Energy.Energy'"));
    if (Material.Succeeded())
    {
        ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
    }
    ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
    ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
    ProjectileMeshComponent->SetupAttachment(RootComponent);
    
    // Delete the projectile after 3 seconds.
    InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void ABaseProjectile::FireInDirection(const FVector& ShootDirection, AActor* ingoreActor)
{
    TArray<AActor*> ingoreActors;
    ingoreActors.Add(ingoreActor);
    ProjectileMeshComponent->MoveIgnoreActors = ingoreActors;
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
    //{
    //    GLog->Log("Hit physics");
    //  //  OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    //}


    ////hit enemy?
    //AActor* actor = Cast<AActor>(Hit.Actor);
    //if (actor)
    //{
    //    GLog->Log("Hit Something " + Hit.Actor->GetName());
    //   /* GLog->Log("Hit Actor");
    //    ACharacter* character = Cast<ACharacter>(actor);
    //    if(character)
    //    {
    //        GLog->Log("Hit character");
    //        ABaseAICharacter* hitAI = Cast<ABaseAICharacter>(actor);
    //        if (hitAI)
    //        {*/
    //            GLog->Log("Hit AI!!!");
    //            ABaseAIEnemy* enemy = Cast<ABaseAIEnemy>(actor);
    //            if (enemy)
    //            {
    //                GLog->Log("Hit Enemy");
    //            }
    //    /*    }
    //    } */           
    //}
    
    Destroy();
}

