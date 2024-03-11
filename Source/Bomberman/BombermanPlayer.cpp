// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanPlayer.h"

// Sets default values
ABombermanPlayer::ABombermanPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABombermanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABombermanPlayer::MoveVertical(float Value)
{
	AddMovementInput(FVector::ForwardVector,Value);
}

void ABombermanPlayer::MoveHorizontal(float Value)
{
	AddMovementInput(FVector::RightVector,Value);
}

// Called every frame
void ABombermanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABombermanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveVertical", this, &ABombermanPlayer::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ABombermanPlayer::MoveHorizontal);
}

