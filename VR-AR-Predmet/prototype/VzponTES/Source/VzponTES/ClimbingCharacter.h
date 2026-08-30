#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ClimbingCharacter.generated.h"

class UCameraComponent;
class UMotionControllerComponent;
class USphereComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * VR igralec z mehaniko "hand-over-hand" plezanja: dokler je igralec prijet (grip)
 * na oprijemu (AClimbHold), se telo premika glede na inverzno gibanje roke od zadnjega framea.
 *
 * Namestitev v UE Editorju:
 *  1. Ustvari Blueprint podrazred BP_ClimbingCharacter (Parent Class = VzponClimbingCharacter).
 *  2. Ustvari Enhanced Input assete: IMC_VR (Input Mapping Context), IA_GripLeft, IA_GripRight
 *     (Digital bool), vezane na Motion Controller (L)/(R) Trigger ali Grip osi.
 *  3. V BP_ClimbingCharacter defaultih nastavi VRMappingContext/GripLeftAction/GripRightAction.
 *  4. Nastavi BP_ClimbingCharacter kot Default Pawn Class v GameMode.
 */
UCLASS()
class VZPONTES_API AVzponClimbingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVzponClimbingCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UMotionControllerComponent* LeftHandController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	UMotionControllerComponent* RightHandController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	USphereComponent* LeftGrabSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR")
	USphereComponent* RightGrabSphere;

	// Assign v Blueprint podrazredu (BP_ClimbingCharacter) - glej opombo zgoraj.
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* VRMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* GripLeftAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* GripRightAction;

	UPROPERTY(EditAnywhere, Category = "Climbing")
	float GrabRadius = 15.f;

	void OnGripLeftStarted(const FInputActionValue& Value);
	void OnGripLeftCompleted(const FInputActionValue& Value);
	void OnGripRightStarted(const FInputActionValue& Value);
	void OnGripRightCompleted(const FInputActionValue& Value);

private:
	bool bLeftGripping = false;
	bool bRightGripping = false;
	FVector LeftLastLocation = FVector::ZeroVector;
	FVector RightLastLocation = FVector::ZeroVector;

	bool IsNearClimbHold(USphereComponent* GrabSphere) const;
};
