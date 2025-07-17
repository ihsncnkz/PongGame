// Fill out your copyright notice in the Description page of Project Settings.

#include "PAIPaddle.h"
#include "ABall.h"

// Sets default values
APAIPaddle::APAIPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = PaddleMesh;

}

// Called when the game starts or when spawned
void APAIPaddle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APAIPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BallRef)
	{
		FVector MyLocation = GetActorLocation();
		FVector BallLocation = BallRef->GetActorLocation();

		float DeltaY = BallLocation.Y - MyLocation.Y;

		if (FMath::Abs(DeltaY) > 10.f)
		{
			float Direction = FMath::Sign(DeltaY);
			float MoveStep = Direction * MoveSpeed * DeltaTime;

			if (FMath::Abs(MoveStep) > FMath::Abs(DeltaY))
			{
				MoveStep = DeltaY;
			}

			MyLocation.Y += MoveStep;
			SetActorLocation(MyLocation);

			FVector PaddleExtant = PaddleMesh->GetStaticMesh() ? PaddleMesh->GetStaticMesh()->GetBoundingBox().GetExtent() : FVector(0, 50, 0);
			float PaddleHalfHeight = PaddleExtant.Y;

			MyLocation.Y = FMath::Clamp(MyLocation.Y, MinY + PaddleHalfHeight, MaxY - PaddleHalfHeight);

			SetActorLocation(MyLocation);
		}
	}
}

// Called to bind functionality to input
void APAIPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

