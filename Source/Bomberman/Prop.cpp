// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop.h"
#include "BombermanPlayer.h"

// Sets default values
AProp::AProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	Prop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Prop"));
	Prop->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProp::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AProp::OnOverlapBegin);
}

void AProp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	ABombermanPlayer* Player = Cast<ABombermanPlayer>(OtherActor);
	if (Player) {
		Player->ExplodeIntensity++;
		Destroy();
	}
}

// Called every frame
void AProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

