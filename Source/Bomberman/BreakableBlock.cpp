// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableBlock.h"
#include "BombermanGameMode.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABreakableBlock::ABreakableBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BreakableBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BreakableBlock"));
	RootComponent = BreakableBlock;
}

// Called when the game starts or when spawned
void ABreakableBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableBlock::OnDestroy()
{
	if(FMath::RandRange(0,1)<DropPropOdds)
		GetWorld()->SpawnActor<AProp>(Prop, GetActorLocation(), FRotator::ZeroRotator);
	Cast<ABombermanGameMode>(UGameplayStatics::GetGameMode(this))->BreakableBlockNum--;
	Destroy();
}

// Called every frame
void ABreakableBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

