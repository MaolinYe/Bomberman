// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockGenerator.h"

// Sets default values
ABlockGenerator::ABlockGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FClassFinder<ABlock> UB(TEXT("/Game/Blueprint/BP_Block"));
	//Block = UB.Class;
	//static ConstructorHelpers::FClassFinder<ABreakableBlock>BB(TEXT("/Game/Blueprint/BP_BreakableBlock"));
	//BreakableBlock = BB.Class;
	SpawnPlayerPositions = {
	FIntPoint(0, 0), FIntPoint(0, 1), FIntPoint(1, 0),
	FIntPoint(Width - 1, 0), FIntPoint(Width - 1, 1), FIntPoint(Width - 2, 0),
	FIntPoint(0, Height - 1), FIntPoint(0, Height - 2), FIntPoint(1, Height - 1),
	FIntPoint(Width - 1, Height - 1), FIntPoint(Width - 1, Height - 2), FIntPoint(Width - 2, Height - 1)
	};
}

// Called when the game starts or when spawned
void ABlockGenerator::BeginPlay()
{
	Super::BeginPlay();
	SpawnBlock(); // 必须在对象完全初始化之后调用，否则GetWorld返回nullptr
	FindSpawnBBPosition();
	SpawnBreakBlock();
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

void ABlockGenerator::FindSpawnBBPosition()
{
	for (int i = 0; i < Width; i++) {
		for (int j = 0; j < Height; j++) {
			if (SpawnPlayerPositions.Contains(FIntPoint(i, j))) {
				continue;
			}
			if (i % 2 == 0 || j % 2 == 0) {
				FVector Position = FVector((i - Width / 2) * BlockSize + 50, (j - Height / 2) * BlockSize + 50, 150);
				BreakBlockPositions.Add(Position);
			}
		}
	}
}

void ABlockGenerator::SpawnBreakBlock()
{
	int BreakBlockNum = BreakBlockPositions.Num() * BlockDensity;
	for (int i = 0; i < BreakBlockNum; i++) {
		int Index = FMath::RandRange(0, BreakBlockPositions.Num() - 1);
		GetWorld()->SpawnActor<ABreakableBlock>(BreakableBlock, BreakBlockPositions[Index], FRotator::ZeroRotator);
		BreakBlockPositions.RemoveAt(Index);
	}
}
