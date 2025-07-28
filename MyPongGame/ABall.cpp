// Fill out your copyright notice in the Description page of Project Settings.


#include "ABall.h"
#include "PongGameState.h"
#include "PAIPaddle.h"

constexpr float MaxBounceAngle = 60.f;

// Sets default values
AABall::AABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	RootComponent = BallMesh;

	BallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BallMesh->SetCollisionProfileName(TEXT("BlockAll"));

	BallMesh->SetSimulatePhysics(false);

	MaxX = 800.f;
	MinX = -800.f;
	MaxY = 400.f;
	MinY = -400.f;

	MoveSpeed = 800.f;
	InitialMoveSpeed = 800.f;
	SpeedIncreaseRate = 10.f;
}

// Called when the game starts or when spawned
void AABall::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	float Angle = FMath::FRandRange(-30.f, 30.f);
	float Radian = FMath::DegreesToRadians(Angle);

	float X_Direction = FMath::RandBool() ? 1.f : -1.f;
	float Y_Direction = FMath::RandBool() ? 1.f : -1.f;

	Velocity = FVector(FMath::Cos(Radian) * X_Direction, FMath::Sin(Radian) * Y_Direction, 0.f) * MoveSpeed;
}

// Called every frame
void AABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APongGameState* gs = GetWorld()->GetGameState<APongGameState>();
	if (gs)
	{
		if (!gs->bGameStarted)
		{
			return;
		}
	}

	MoveSpeed += SpeedIncreaseRate * DeltaTime;

	if (!Velocity.IsNearlyZero())
	{
		Velocity = Velocity.GetSafeNormal() * MoveSpeed;
	}

	FVector NewLocation = GetActorLocation() + Velocity * DeltaTime;

	if (NewLocation.Y > MaxY || NewLocation.Y < MinY)
	{
		Velocity.Y *= -1.f;
		NewLocation.Y = FMath::Clamp(NewLocation.Y, MinY, MaxY);
	}

	if (NewLocation.X > MaxX)
	{
		if (CheckPaddleCollision(PlayerPaddleRef))
		{
			/* Old Code
			Velocity.X *= -1.f;

			FVector PaddleLocation = PlayerPaddleRef->GetActorLocation();
			FVector PaddleExtent = PlayerPaddleRef->GetSimpleCollisionCylinderExtent();
			NewLocation.X = PaddleLocation.X - PaddleExtent.X - 5.f;
			return;
			*/

			FVector PaddleLocation = PlayerPaddleRef->GetActorLocation();
			FVector PaddleExtent = PlayerPaddleRef->GetSimpleCollisionCylinderExtent();

			float PaddleCenterY = PaddleLocation.Y;
			float HitPointY = NewLocation.Y;

			float Offset = HitPointY - PaddleCenterY;
			float PaddleHeight = PaddleExtent.Y;
			float Normalized = FMath::Clamp(Offset / PaddleHeight, -1.f, 1.f);

			float Angle = Normalized * MaxBounceAngle;
			float Speed = Velocity.Size();
			float OldSign = FMath::Sign(Velocity.X);

			Velocity.X = Speed * FMath::Cos(FMath::DegreesToRadians(Angle)) * -OldSign;
			Velocity.Y = Speed * FMath::Sin(FMath::DegreesToRadians(Angle));

			NewLocation.X = PaddleLocation.X - PaddleExtent.X + 5.f;
		}
		else
		{
			if (gs)
			{
				gs->AIScore++;

				if (gs->AIScore == 5)
				{
					gs->EndGame(false);
				}
			}


			ResetBall();
			return;
		}
	}

	else if (NewLocation.X < MinX)
	{
		if (CheckPaddleCollision(AIPaddleRef))
		{
			// Velocity.X *= -1.f; Old Code

			FVector PaddleLocation = AIPaddleRef->GetActorLocation();
			FVector PaddleExtent = AIPaddleRef->GetSimpleCollisionCylinderExtent();

			float PaddleCenterY = PaddleLocation.Y;
			float HitPointY = NewLocation.Y;

			float Offset = HitPointY - PaddleCenterY;
			float PaddleHeight = PaddleExtent.Y;
			float Normalized = FMath::Clamp(Offset / PaddleHeight, -1.f, 1.f);

			float Angle = Normalized * MaxBounceAngle;
			float Speed = Velocity.Size();
			float OldSign = FMath::Sign(Velocity.X);

			Velocity.X = Speed * FMath::Cos(FMath::DegreesToRadians(Angle)) * -OldSign;
			Velocity.Y = Speed * FMath::Sin(FMath::DegreesToRadians(Angle));


			NewLocation.X = PaddleLocation.X + PaddleExtent.X - 5.f;
		}
		else
		{
			if (gs)
			{
				gs->PlayerScore++;

				if (gs->PlayerScore == 5)
				{
					gs->EndGame(true);
				}
			}

			ResetBall();
			return;
		}
	}
	SetActorLocation(NewLocation, true);


	
}

bool AABall::CheckPaddleCollision(AActor* Paddle)
{
	if (!Paddle) return false;

	FVector BallLocation = GetActorLocation();
	FVector PaddleLocation = Paddle->GetActorLocation();
	FVector PaddleExtent = Paddle->GetSimpleCollisionCylinderExtent();

	float PaddleYMin = PaddleLocation.Y - PaddleExtent.Y;
	float PaddleYMax = PaddleLocation.Y + PaddleExtent.Y;

	return BallLocation.Y >= PaddleYMin && BallLocation.Y <= PaddleYMax;
}

void AABall::ResetBall()
{
	SetActorLocation(StartLocation);

	MoveSpeed = InitialMoveSpeed;

	float Angle = FMath::FRandRange(-30.f, 30.f);
	float Radian = FMath::DegreesToRadians(Angle);

	float X_Direction = FMath::RandBool() ? 1.f : -1.f;
	float Y_Direction = FMath::RandBool() ? 1.f : -1.f;

	Velocity = FVector(FMath::Cos(Radian) * X_Direction, FMath::Sin(Radian) * Y_Direction, 0.f) * MoveSpeed;
}