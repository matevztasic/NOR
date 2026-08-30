#include "ClimbHold.h"
#include "Components/StaticMeshComponent.h"

AClimbHold::AClimbHold()
{
	PrimaryActorTick.bCanEverTick = false;

	HoldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoldMesh"));
	RootComponent = HoldMesh;
	HoldMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	// Uporabljeno za identifikacijo v AVzponClimbingCharacter::IsNearClimbHold
	Tags.Add(TEXT("ClimbHold"));
}

void AClimbHold::BeginPlay()
{
	Super::BeginPlay();
}
