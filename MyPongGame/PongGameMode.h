// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "PongGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYPONGGAME_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UUserWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> EndGameWidgetClass;
	
	UUserWidget* EndGameWidget;

	UFUNCTION(BlueprintCallable)
	void ShowEndGameWidget(bool bPlayerOrAI);
};
