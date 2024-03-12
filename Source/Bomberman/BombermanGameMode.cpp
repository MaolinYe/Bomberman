// Fill out your copyright notice in the Description page of Project Settings.


#include "BombermanGameMode.h"
#include "Kismet/KismetStringLibrary.h"
#include "BombmanHUD.h"
void ABombermanGameMode::BeginPlay()
{
	Super::BeginPlay();
	BombmanHUD = CreateWidget<UBombmanHUD>(GetWorld(), LoadClass<UBombmanHUD>(this, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/WBP_HUD.WBP_HUD_C'")));
	BombmanHUD->AddToViewport();
}
ABombermanGameMode::ABombermanGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ABombermanGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    CountdownTime -= DeltaSeconds;
    FTimespan CountdownTimespan = FTimespan::FromSeconds(CountdownTime);
    FString FormattedTime = FString::Printf(TEXT("%02d:%02d"), CountdownTimespan.GetMinutes(), CountdownTimespan.GetSeconds());
    TimeText = FText::FromString(FormattedTime);
    BombmanHUD->SetRemainTimer(TimeText);
}
