// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockGenerator.h"

// Sets default values
ABlockGenerator::ABlockGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlockGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnBlock(); // 必须在对象完全初始化之后调用，否则GetWorld返回nullptr
}

// Called every frame
void ABlockGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockGenerator::SpawnBlock()
{
	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			if (i % 2 != 0 && j % 2 != 0) {
				FVector Position = FVector((i - Width / 2) * BlockSize + 50, (j - Height / 2) * BlockSize + 50, 150);
				GetWorld()->SpawnActor<ABlock>(Block, Position, FRotator::ZeroRotator);
			}
		}
	}
}