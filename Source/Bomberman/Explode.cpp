// Fill out your copyright notice in the Description page of Project Settings.


#include "Explode.h"

// Sets default values
AExplode::AExplode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExplode::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandleExplode, this, &AExplode::Explode, ExplodeTime);
}

void AExplode::Explode()
{
	Destroy();
}

// Called every frame
void AExplode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

