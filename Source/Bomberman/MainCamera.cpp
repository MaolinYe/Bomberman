// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"
#include "Kismet/GameplayStatics.h"
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();
	PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetViewTargetWithBlend(this, 0);
}
