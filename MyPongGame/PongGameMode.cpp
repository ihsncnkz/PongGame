// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Camera/CameraActor.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"


void APongGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuWidgetClass)
    {
        MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();

            APlayerController* PC = GetWorld()->GetFirstPlayerController(); 
            if (PC)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());
                PC->SetInputMode(InputMode);
                PC->bShowMouseCursor = true;
            }
        }
    }

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
