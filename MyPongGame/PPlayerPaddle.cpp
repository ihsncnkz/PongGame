// Fill out your copyright notice in the Description page of Project Settings.


#include "PPlayerPaddle.h"

// Sets default values
APPlayerPaddle::APPlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = PaddleMesh;
}

// Called when the game starts or when spawned
void APPlayerPaddle::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	
}

void APPlayerPaddle::MoveLeftStart(const FInputActionInstance& Instance)
{
	CurrentInput = FVector(0.f, 1.f, 0.f);
}

void APPlayerPaddle::MoveLeftStop(const FInputActionInstance& Instance)
{
	//if (CurrentInput.Y < 0)
	CurrentInput = FVector::ZeroVector;
}

void APPlayerPaddle::MoveRightStart(const FInputActionInstance& Instance)
{
	CurrentInput = FVector(0.f, -1.f, 0.f);
}

void APPlayerPaddle::MoveRightStop(const FInputActionInstance& Instance)
{
	//if (CurrentInput.Y > 0)
	CurrentInput = FVector::ZeroVector;
}

// Called every frame
void APPlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentInput.IsNearlyZero())
	{
		FVector Movement = CurrentInput * MoveSpeed * DeltaTime;
		AddActorWorldOffset(Movement, true);
	}

}

// Called to bind functionality to input
void APPlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		InputComp->BindAction(LeftAction, ETriggerEvent::Triggered, this, &APPlayerPaddle::MoveLeftStart);
		InputComp->BindAction(LeftAction, ETriggerEvent::Completed, this, &APPlayerPaddle::MoveLeftStop);
		InputComp->BindAction(RightAction, ETriggerEvent::Triggered, this, &APPlayerPaddle::MoveRightStart);
		InputComp->BindAction(RightAction, ETriggerEvent::Completed, this, &APPlayerPaddle::MoveRightStop);
	}
}
