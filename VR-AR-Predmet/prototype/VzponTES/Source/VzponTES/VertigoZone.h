#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VertigoZone.generated.h"

class UBoxComponent;
class UAudioComponent;
class USoundBase;

/**
 * Cona na vrhu elektrarne (glej Scena 3 v /vaja-02/scenes.md), ki ob vstopu igralca
 * sproži vizualni (vinjetiranje) in zvočni (veter) učinek vrtoglavice/višine.
 *
 * Namestitev v UE Editorju:
 *  1. Ustvari Blueprint podrazred BP_VertigoZone (Parent = VertigoZone).
 *  2. Nastavi WindLoopSound na zvočni posnetek vetra, postavi TriggerVolume okoli roba ploščadi.
 */
UCLASS()
class VZPONTES_API AVertigoZone : public AActor
{
	GENERATED_BODY()

public:
	AVertigoZone();

	UPROPERTY(EditAnywhere, Category = "Vertigo")
	float VignetteIntensity = 0.6f;

	UPROPERTY(EditAnywhere, Category = "Vertigo")
	USoundBase* WindLoopSound;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* TriggerVolume;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* WindAudio;

	UFUNCTION()
	void OnPlayerEnterHeight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerExitHeight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
