// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameState.generated.h"

/**
 * 
 */
UCLASS()
class MYPONGGAME_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	
	APongGameState();

	UFUNCTION(BlueprintCallable)
	FString GetGameTimeText() const;

protected:
	
	virtual void Tick(float DeltaSeconds) override;

private:
	
	float ElapsedTime;

};
