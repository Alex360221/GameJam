// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAICharacter.h"
#include "BaseAIEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API ABaseAIEnemy : public ABaseAICharacter
{
	GENERATED_BODY()
public:
	ABaseAIEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float attackRange = 1000;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool randomWalking = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float health = 100.f;

public: 
	void DamageEnemy(float damageAmount);
	UFUNCTION(BlueprintCallable)
		void DamagePlayer(float damageAmount);

private:
	bool moveToPlayer = false;

	bool ShouldStartMove();
	bool ShouldStopMove();
	bool WithinDistance(float dis);

	void AttackPlayer(float dt);
	bool attackPlayer = false;
	float attackTimer = 1.f;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool runAttack = false;
};
