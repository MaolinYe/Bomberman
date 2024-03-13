// Fill out your copyright notice in the Description page of Project Settings.


#include "BombmanHUD.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UBombmanHUD::SetRemainTimer(FText TimerText)
{
	RemainTimer->SetText(TimerText);
}

void UBombmanHUD::SetGameResult(bool Win)
{
	if (Win)
		GameResult->SetText(WinText);
	else
		GameResult->SetText(LoseText);
	MenuBackground->SetVisibility(ESlateVisibility::Visible);
}
