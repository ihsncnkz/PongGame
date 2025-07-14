// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "PPlayerPaddle.generated.h"

UCLASS()
class MYPONGGAME_API APPlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APPlayerPaddle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PaddleMesh;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LeftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RightAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 400.f;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveLeftStart(const FInputActionInstance& Instance);
	void MoveLeftStop(const FInputActionInstance& Instance);

	void MoveRightStart(const FInputActionInstance& Instance);
	void MoveRightStop(const FInputActionInstance& Instance);

private:

	FVector CurrentInput;

};
