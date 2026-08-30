#include "VertigoZone.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

AVertigoZone::AVertigoZone()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;
	TriggerVolume->SetBoxExtent(FVector(300.f, 300.f, 500.f));
	TriggerVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	WindAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("WindAudio"));
	WindAudio->SetupAttachment(RootComponent);
	WindAudio->bAutoActivate = false;
}

void AVertigoZone::BeginPlay()
{
	Super::BeginPlay();

	if (WindLoopSound)
	{
		WindAudio->SetSound(WindLoopSound);
	}

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AVertigoZone::OnPlayerEnterHeight);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AVertigoZone::OnPlayerExitHeight);
}

void AVertigoZone::OnPlayerEnterHeight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character)
	{
		return;
	}

	WindAudio->Play();

	if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))
	{
		FPostProcessSettings VertigoSettings;
		VertigoSettings.bOverride_VignetteIntensity = true;
		VertigoSettings.VignetteIntensity = VignetteIntensity;
		PC->PlayerCameraManager->AddCachedPPBlend(VertigoSettings, 1.f);
	}
}

void AVertigoZone::OnPlayerExitHeight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character)
	{
		return;
	}

	WindAudio->Stop();

	if (APlayerController* PC = Cast<APlayerController>(Character->GetController()))
	{
		FPostProcessSettings VertigoSettings;
		VertigoSettings.bOverride_VignetteIntensity = true;
		VertigoSettings.VignetteIntensity = 0.f;
		PC->PlayerCameraManager->AddCachedPPBlend(VertigoSettings, 1.f);
	}
}
