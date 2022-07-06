// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIEnemy.h"
#include <GameJam/BaseCharacter.h>

ABaseAIEnemy::ABaseAIEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	moveToPlayer = false;
}

void ABaseAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	targetLocation = GetActorLocation();
}

void ABaseAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (health <= 0)
	{
		moveToPlayer = false;
		randomWalking = false;
		targetLocation = GetActorLocation();
	}
	else
	{
		attackTimer += DeltaTime;
		if (WithinDistance(50))
		{
			//GLog->Log("Within distacne to attack");
			moveToPlayer = false;		
			AttackPlayer(DeltaTime);
		}
		else if (!moveToPlayer)
		{
			//should Attack?
			if (WithinDistance(150)) { AttackPlayer(DeltaTime); }
			else
			{
				attackTimer = 0.f;
				if (ShouldStartMove())
				{
					moveToPlayer = true;
					randomWalking = false;
				}
				else
				{
					randomWalking = true;
				}
			}
		}
		else
		{
			if (!ShouldStopMove()) { FollowPlayer(50); }
			else { moveToPlayer = false; }
		}
	}
}

void ABaseAIEnemy::DamageEnemy(float damageAmount)
{
	health -= damageAmount;
}

void ABaseAIEnemy::DamagePlayer(float damageAmount)
{
	if (player)
	{
		if (WithinDistance(150))
		{
			GLog->Log("Damage Player");
			player->currentHealth -= damageAmount;
		}
	}
}

bool ABaseAIEnemy::ShouldStartMove()
{
	if (DisToPlayer() < attackRange)
	{
		GLog->Log("Enemy Start Moving");
		return true;
	}
	return false;
}

bool ABaseAIEnemy::ShouldStopMove()
{
	if (DisToPlayer() < 100)
	{
		GLog->Log("Enemey Stop Moving");
		return true;
	}
	return false;
}

bool ABaseAIEnemy::WithinDistance(float dis)
{
	if (DisToPlayer() < dis)
	{
		return true;
	}
	return false;
}

void ABaseAIEnemy::AttackPlayer(float dt)
{
	if (attackTimer >= 1.f)
	{
		attackTimer = 0.f;
		GLog->Log("Attack player");
		runAttack = true;
		//DamagePlayer(30.f);
	}
}
