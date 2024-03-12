// Fill out your copyright notice in the Description page of Project Settings.


#include "BombmanHUD.h"
#include "Components/TextBlock.h"

void UBombmanHUD::SetRemainTimer(FText TimerText)
{
	RemainTimer->SetText(TimerText);
}
