// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DetaTime)
{
	Super::Tick(DetaTime);
	if(TankInFireRange())
	{
		RotateTurret(tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::CheckFireCondition, fireRate, true);
}

void ATower::CheckFireCondition()
{
	if(TankInFireRange())
	{
		Fire();
	}
}

bool ATower::TankInFireRange()
{
	if(tank)
	{
		float distance = FVector::Dist(GetActorLocation(), tank->GetActorLocation());
		if(distance <= fireRange)
		{
			return true;
		}
	}
	return false;
}
