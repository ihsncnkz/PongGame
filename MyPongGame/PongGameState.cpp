// Fill out your copyright notice in the Description page of Project Settings.

#include "PongGameState.h"

#include "Kismet/GameplayStatics.h"

APongGameState::APongGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	ElapsedTime = 0.0f;
}

void APongGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	ElapsedTime += DeltaSeconds;
}

FString APongGameState::GetGameTimeText() const
{
	int32 TotalSeconds = FMath::FloorToInt(ElapsedTime);
	int32 Minutes = TotalSeconds / 60;
	int32 Seconds = TotalSeconds % 60;

	return FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
}


void APongGameState::EndGame(bool bPlayerOrAI)
{
	if (bPlayerOrAI)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, TEXT("Player Win"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("AI Win"));
	}
}