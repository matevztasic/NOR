#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClimbHold.generated.h"

/**
 * Posamezen oprijem na steni elektrarne. Igralec ga prime prek AVzponClimbingCharacter,
 * ki v svojih Grab-sferah preverja prekrivanje z akterji tega razreda.
 */
UCLASS()
class VZPONTES_API AClimbHold : public AActor
{
	GENERATED_BODY()

public:
	AClimbHold();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Climbing")
	UStaticMeshComponent* HoldMesh;

protected:
	virtual void BeginPlay() override;
};
