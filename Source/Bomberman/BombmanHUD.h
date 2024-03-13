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
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* RemainTimer;
	UPROPERTY(Meta = (BindWidget))
	class UCanvasPanel* MenuBackground;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock* GameResult;
	UPROPERTY(EditAnywhere, Category = "Setting")
	FText WinText = FText::FromString(TEXT("You Win!"));
	UPROPERTY(EditAnywhere, Category = "Setting")
	FText LoseText = FText::FromString(TEXT("You Lost!"));
protected:
	virtual bool Initialize()override;
	UPROPERTY(Meta = (BindWidget))
	class UButton* RestartButton;
	UFUNCTION()
	void Replay();
public:
	void SetRemainTimer(FText TimerText);
	void SetGameResult(bool Win);
};
