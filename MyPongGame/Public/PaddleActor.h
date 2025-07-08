#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaddleActor.generated.h"

UCLASS()
class MYPONGGAME_API APaddleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaddleActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PaddleMesh;
};
