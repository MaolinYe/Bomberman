// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Prop.h"
#include "BreakableBlock.generated.h"

UCLASS()
class BOMBERMAN_API ABreakableBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* BreakableBlock;
	UPROPERTY(EditAnywhere, Category = "DropProp")
	TSubclassOf<AProp>Prop;
	UPROPERTY(EditAnywhere, Category = "DropProp")
	float DropPropOdds = 0.5f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnDestroy();
};
