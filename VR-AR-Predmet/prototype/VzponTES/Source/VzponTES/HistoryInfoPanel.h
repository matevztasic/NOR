#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HistoryInfoPanel.generated.h"

class USphereComponent;
class UWidgetComponent;

/**
 * Interaktivna zgodovinska info-točka med vzponom (glej Scena 2 v /vaja-02/scenes.md).
 * Ko igralec vstopi v TriggerSphere, se prikaže plavajoča informacijska tabla (World-space UMG widget).
 *
 * Namestitev v UE Editorju:
 *  1. Ustvari UMG Widget Blueprint (npr. WBP_HistoryPanel) z Text/Image bindingi na Title/Description/HistoricalImage.
 *  2. Ustvari Blueprint podrazred BP_HistoryInfoPanel (Parent = HistoryInfoPanel), nastavi InfoWidget->WidgetClass = WBP_HistoryPanel.
 *  3. Postavi instance BP_HistoryInfoPanel vzdolž poti vzpona, vsaki nastavi Title/Description/HistoricalImage.
 */
UCLASS()
class VZPONTES_API AHistoryInfoPanel : public AActor
{
	GENERATED_BODY()

public:
	AHistoryInfoPanel();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "History")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "History", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "History")
	class UTexture2D* HistoricalImage;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* TriggerSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* InfoWidget;

	// Sproženo, ko widget postane viden - v Blueprintu/UMG-ju uporabi za vezavo Title/Description/HistoricalImage na UI.
	UFUNCTION(BlueprintImplementableEvent, Category = "History")
	void OnInfoDisplayUpdated();

	UFUNCTION()
	void OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
