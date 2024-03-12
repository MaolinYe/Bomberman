// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BombmanHUD.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBombmanHUD : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(Meta=(BindWidget))
	class UTextBlock* RemainTimer;
public:
	void SetRemainTimer(FText TimerText);
};
