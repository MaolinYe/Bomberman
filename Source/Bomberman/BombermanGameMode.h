// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API ABombermanGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Setting")
	float CountdownTime = 300;
	FText TimeText;
	class UBombmanHUD* BombmanHUD;
	virtual void BeginPlay()override;
public:
	ABombermanGameMode();
	virtual void Tick(float DeltaSeconds)override;
};
