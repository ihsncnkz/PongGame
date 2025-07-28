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

    FString CurrentLevelName = GetWorld()->GetMapName();
    CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

    if (CurrentLevelName == TEXT("MainMenu"))
    {
        if (MainMenuWidgetClass)
        {
            MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
            if (MainMenuWidget)
            {
                APlayerController* PC = GetWorld()->GetFirstPlayerController();
                if (PC)
                {
                    PC->bShowMouseCursor = true;
                }

                MainMenuWidget->AddToViewport();
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

void APongGameMode::ShowEndGameWidget(bool bPlayerOrAI)
{
    if (EndGameWidgetClass)
    {
        EndGameWidget = CreateWidget<UUserWidget>(GetWorld(), EndGameWidgetClass);
        if (EndGameWidget) 
        {
            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                PC->bShowMouseCursor = true;
            }

            EndGameWidget->AddToViewport();

            UFunction* SetWinnerFunc = EndGameWidget->FindFunction(FName("SetWinner"));
            if (SetWinnerFunc)
            {
                struct
                {
                    bool bPlayerOrAI;
                } Params;

                Params.bPlayerOrAI = bPlayerOrAI;
                EndGameWidget->ProcessEvent(SetWinnerFunc, &Params);
            }
        }
    }
}
