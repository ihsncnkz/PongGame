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

	UFUNCTION(BlueprintCallable)
	void EndGame(bool bPlayerOrAI);

	UPROPERTY(BlueprintReadWrite)
	int32 PlayerScore = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 AIScore = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bGameStarted = true;


protected:
	
	virtual void Tick(float DeltaSeconds) override;

private:
	
	float ElapsedTime;

};
