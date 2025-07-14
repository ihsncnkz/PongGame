// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PPlayerPaddle.h"
#include "PAIPaddle.h"
#include "ABall.generated.h"

UCLASS()
class MYPONGGAME_API AABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool CheckPaddleCollision(AActor* Paddle);

	UFUNCTION()
	void ResetBall();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PaddleRefs")
	APPlayerPaddle* PlayerPaddleRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PaddleRefs")
	APAIPaddle* AIPaddleRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BallMesh;

	FVector Velocity;

	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "BallAction")
	float MoveSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = "BallAction")
	float MaxX = 800.f;

	UPROPERTY(EditAnywhere, Category = "BallAction")
	float MinX = -800.f;

	UPROPERTY(EditAnywhere, Category = "BallAction")
	float MaxY = 400.f;

	UPROPERTY(EditAnywhere, Category = "BallAction")
	float MinY = -400.f;
};
