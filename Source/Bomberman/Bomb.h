// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Explode.h"
#include "Bomb.generated.h"

UCLASS()
class BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* Bomb;
	UPROPERTY(EditAnywhere, Category = "Component")
	UBoxComponent* BoxCollision;
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	FTimerHandle TimerHandleExplode;
	UPROPERTY(EditAnywhere, Category = "Explode")
	float ExplodeTime = 1;
	void Explode();
	UPROPERTY(EditAnywhere, Category = "Explode")
	TSubclassOf<AExplode>ExplodeEffect;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
