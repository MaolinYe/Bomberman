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
	PlayerInputComponent->BindAction("SpawnBomb", IE_Pressed, this, &ABombermanPlayer::SpawnBomb);
}

void ABombermanPlayer::SpawnBomb()
{
	if (Bomb) {
		FActorSpawnParameters Parameters;
		Parameters.Owner = this;
		FVector Location = GetActorLocation();
		auto Modify = [](int i)->int {
			i = i - 50;
			int mode = i % 100;
			i = i - mode;
			if (mode > 50)
				i = i + 100;
			return i + 50;
			};
		Location.X = Modify((int)Location.X);
		Location.Y = Modify((int)Location.Y);
		Location.Z = 140;
		GetWorld()->SpawnActor<ABomb>(Bomb,Location , FRotator::ZeroRotator,Parameters);
	}
}

