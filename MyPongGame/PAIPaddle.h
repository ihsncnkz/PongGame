// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "PAIPaddle.generated.h"

class AABall;

UCLASS()
class MYPONGGAME_API APAIPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APAIPaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PaddleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	AABall* BallRef;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MoveSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MinY = -400.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float MaxY = 400.f;
};
