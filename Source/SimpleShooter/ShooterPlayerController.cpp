// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (HUD)
	{
		HUD->RemoveFromParent();
	}

	AddScreenToViewport(bIsWinner ? WinScreenClass : LoseScreenClass);
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = AddScreenToViewport(HUDClass);
}

UUserWidget* AShooterPlayerController::AddScreenToViewport(TSubclassOf<UUserWidget> widgetClass)
{
	UUserWidget* ScreenToAdd = CreateWidget(this, widgetClass);

	if (ScreenToAdd)
	{
		ScreenToAdd->AddToViewport();
	}

	return ScreenToAdd;
}

