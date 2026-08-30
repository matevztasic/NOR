#include "ClimbingCharacter.h"
#include "ClimbHold.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

AVzponClimbingCharacter::AVzponClimbingCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Med plezanjem igralca premikamo ročno (AddActorWorldOffset), zato izklopimo gravitacijo
	// privzetega gibanja; v poznejši fazi razvoja je smiselno dodati ločen "prosti pad" state.
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	GetCharacterMovement()->GravityScale = 0.f;

	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(GetCapsuleComponent());
	VRCamera->bUsePawnControlRotation = false;

	LeftHandController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHandController"));
	LeftHandController->SetupAttachment(GetCapsuleComponent());
	LeftHandController->SetTrackingMotionSource(FName("Left"));

	RightHandController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHandController"));
	RightHandController->SetupAttachment(GetCapsuleComponent());
	RightHandController->SetTrackingMotionSource(FName("Right"));

	LeftGrabSphere = CreateDefaultSubobject<USphereComponent>(TEXT("LeftGrabSphere"));
	LeftGrabSphere->SetupAttachment(LeftHandController);
	LeftGrabSphere->SetSphereRadius(GrabRadius);
	LeftGrabSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	RightGrabSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RightGrabSphere"));
	RightGrabSphere->SetupAttachment(RightHandController);
	RightGrabSphere->SetSphereRadius(GrabRadius);
	RightGrabSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AVzponClimbingCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (VRMappingContext)
			{
				Subsystem->AddMappingContext(VRMappingContext, 0);
			}
		}
	}
}

void AVzponClimbingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (GripLeftAction)
		{
			EnhancedInput->BindAction(GripLeftAction, ETriggerEvent::Started, this, &AVzponClimbingCharacter::OnGripLeftStarted);
			EnhancedInput->BindAction(GripLeftAction, ETriggerEvent::Completed, this, &AVzponClimbingCharacter::OnGripLeftCompleted);
		}
		if (GripRightAction)
		{
			EnhancedInput->BindAction(GripRightAction, ETriggerEvent::Started, this, &AVzponClimbingCharacter::OnGripRightStarted);
			EnhancedInput->BindAction(GripRightAction, ETriggerEvent::Completed, this, &AVzponClimbingCharacter::OnGripRightCompleted);
		}
	}
}

bool AVzponClimbingCharacter::IsNearClimbHold(USphereComponent* GrabSphere) const
{
	if (!GrabSphere)
	{
		return false;
	}

	TArray<AActor*> Overlapping;
	GrabSphere->GetOverlappingActors(Overlapping, AClimbHold::StaticClass());
	return Overlapping.Num() > 0;
}

void AVzponClimbingCharacter::OnGripLeftStarted(const FInputActionValue& Value)
{
	if (IsNearClimbHold(LeftGrabSphere))
	{
		bLeftGripping = true;
		LeftLastLocation = LeftHandController->GetComponentLocation();
	}
}

void AVzponClimbingCharacter::OnGripLeftCompleted(const FInputActionValue& Value)
{
	bLeftGripping = false;
}

void AVzponClimbingCharacter::OnGripRightStarted(const FInputActionValue& Value)
{
	if (IsNearClimbHold(RightGrabSphere))
	{
		bRightGripping = true;
		RightLastLocation = RightHandController->GetComponentLocation();
	}
}

void AVzponClimbingCharacter::OnGripRightCompleted(const FInputActionValue& Value)
{
	bRightGripping = false;
}

void AVzponClimbingCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bLeftGripping && !bRightGripping)
	{
		return;
	}

	FVector TotalDelta = FVector::ZeroVector;
	int32 GripCount = 0;

	if (bLeftGripping)
	{
		const FVector CurrentLocation = LeftHandController->GetComponentLocation();
		TotalDelta += (CurrentLocation - LeftLastLocation);
		LeftLastLocation = CurrentLocation;
		GripCount++;
	}

	if (bRightGripping)
	{
		const FVector CurrentLocation = RightHandController->GetComponentLocation();
		TotalDelta += (CurrentLocation - RightLastLocation);
		RightLastLocation = CurrentLocation;
		GripCount++;
	}

	if (GripCount > 0)
	{
		// Telo premaknemo v nasprotni smeri gibanja roke - občutek, da se igralec "povleče" navzgor.
		const FVector AverageDelta = TotalDelta / GripCount;
		AddActorWorldOffset(-AverageDelta, true);
	}
}
