// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"

APongGameMode::APongGameMode()
{
	DefaultPawnClass = nullptr;
}

void APongGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), FoundCameras);

	if (FoundCameras.Num() > 0)
	{
		ACameraActor* Camera = Cast<ACameraActor>(FoundCameras[0]);
		if (Camera)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PC)
			{
				PC->SetViewTarget(Camera);
			}
		}
	}
}
