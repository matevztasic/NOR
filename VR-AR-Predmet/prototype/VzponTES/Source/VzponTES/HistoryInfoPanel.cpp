#include "HistoryInfoPanel.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"

AHistoryInfoPanel::AHistoryInfoPanel()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	RootComponent = TriggerSphere;
	TriggerSphere->SetSphereRadius(250.f);
	TriggerSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	InfoWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InfoWidget"));
	InfoWidget->SetupAttachment(RootComponent);
	InfoWidget->SetWidgetSpace(EWidgetSpace::World);
	InfoWidget->SetDrawSize(FVector2D(500.f, 350.f));
	InfoWidget->SetVisibility(false);
}

void AHistoryInfoPanel::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AHistoryInfoPanel::OnPlayerEnter);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AHistoryInfoPanel::OnPlayerExit);
}

void AHistoryInfoPanel::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		InfoWidget->SetVisibility(true);
		OnInfoDisplayUpdated();
	}
}

void AHistoryInfoPanel::OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACharacter>(OtherActor))
	{
		InfoWidget->SetVisibility(false);
	}
}
