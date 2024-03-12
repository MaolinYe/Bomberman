// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explode.generated.h"

UCLASS()
class BOMBERMAN_API AExplode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplode();
	UPROPERTY(BlueprintReadWrite, Category = "Explode")
	float ExplodeIntensity = 1;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle TimerHandleExplode;
	UPROPERTY(EditAnywhere, Category = "Explode")
	float ExplodeTime = 1;
	void Explode();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
