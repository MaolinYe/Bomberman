// Fill out your copyright notice in the Description page of Project Settings.


#include "BombmanHUD.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "BombermanGameMode.h"
#include "Kismet/GameplayStatics.h"

bool UBombmanHUD::Initialize()
{
	if(!Super::Initialize())
	return false;
	RestartButton->OnClicked.AddDynamic(this, &UBombmanHUD::Replay);
	return true;
}

void UBombmanHUD::Replay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("Hey, restart."));
	Cast<ABombermanGameMode>(UGameplayStatics::GetGameMode(this))->Restart();
}

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
