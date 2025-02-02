// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "BreakableBlock.h"
#include "BombermanGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BombermanPlayer.h"
// Sets default values
ABomb::ABomb()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	Bomb = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb"));
	Bomb->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABomb::OnOverlapEnd);
	GetWorldTimerManager().SetTimer(TimerHandleExplode, this, &ABomb::Explode, ExplodeTime);
	GameMode = Cast<ABombermanGameMode>(UGameplayStatics::GetGameMode(this));
}

void ABomb::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetOwner()) {
		BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	}
}

void ABomb::Explode()
{
	if (ExplodeEffect)
		GetWorld()->SpawnActor<AExplode>(ExplodeEffect, GetActorLocation(), FRotator::ZeroRotator);
	for (int i = 1; i <= ExplodeIntensity; i++) {
		ExplodeHere(GetActorLocation() + i * FVector(100, 0, 0));
		ExplodeHere(GetActorLocation() + i * FVector(0, 100, 0));
		ExplodeHere(GetActorLocation() + i * FVector(-100, 0, 0));
		ExplodeHere(GetActorLocation() + i * FVector(0, -100, 0));
	}
	Destroy();
}

void ABomb::ExplodeHere(FVector Location)
{
	if (ExplodeEffect)
		GetWorld()->SpawnActor<AExplode>(ExplodeEffect, Location, FRotator::ZeroRotator);
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), Location, ECollisionChannel::ECC_WorldStatic, CollisionParams))
	{
		ABreakableBlock*BreakBlock = Cast<ABreakableBlock>(HitResult.GetActor());
		if (BreakBlock) {
			BreakBlock->OnDestroy();
		}
		else {
			ABombermanPlayer* Player = Cast<ABombermanPlayer>(HitResult.GetActor());
			if (Player) {
				GameMode->GameOver(false);
			}
		}
	}
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

