// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class BOMBERMAN_API ABlock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* Block;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
