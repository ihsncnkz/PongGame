#include "PaddleActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APaddleActor::APaddleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	RootComponent = PaddleMesh;

}

// Called when the game starts or when spawned
void APaddleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaddleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}