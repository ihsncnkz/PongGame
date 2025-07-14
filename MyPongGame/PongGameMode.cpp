// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"


void APongGameMode::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> Cameras;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MainCamera"), Cameras);

    if (Cameras.Num() > 0)
    {
        ACameraActor* CameraActor = Cast<ACameraActor>(Cameras[0]);
        if (CameraActor)
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            if (PC)
            {
                PC->SetViewTarget(CameraActor); 
            }
        }
    }
}
