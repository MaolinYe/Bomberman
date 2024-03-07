// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.h"
#include "BlockGenerator.generated.h"

UCLASS()
class BOMBERMAN_API ABlockGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABlockGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Block Generation")
	TSubclassOf<class ABlock>Block;
	UPROPERTY(EditAnywhere, Category = "Block Generation|Setting")
	int Height = 15;
	UPROPERTY(EditAnywhere, Category = "Block Generation|Setting")
	int Width = 15;
	UPROPERTY(EditAnywhere, Category = "Block Generation|Setting")
	int BlockSize = 100;
	void SpawnBlock();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
