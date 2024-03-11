// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bomb.h"
#include "BombermanPlayer.generated.h"

UCLASS()
class BOMBERMAN_API ABombermanPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABombermanPlayer();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, Category = "Bomb")
	TSubclassOf<ABomb>Bomb;
	virtual void BeginPlay() override;
	void MoveVertical(float Value);
	void MoveHorizontal(float Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SpawnBomb();
};
