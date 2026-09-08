#include "ExitPortal.h"

#include "PortalChargeWidget.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputPlayer/PlayerCharacter.h"
#include "TheHuntGameInstance.h"

AExitPortal::AExitPortal()
{
    PrimaryActorTick.bCanEverTick = true;

    Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
    RootComponent = Trigger;
    Trigger->SetSphereRadius(150.f);
    Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // World-space charge widget — attach so you can position it in the editor
    ChargeWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("ChargeWidget"));
    ChargeWidgetComp->SetupAttachment(RootComponent);
    ChargeWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);  // always faces camera, readable
    ChargeWidgetComp->SetDrawSize(FVector2D(200.f, 200.f));   // size of the radial bar
    ChargeWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 150.f)); // float above portal
}

void AExitPortal::BeginPlay()
{
    Super::BeginPlay();
    Trigger->OnComponentBeginOverlap.AddDynamic(this, &AExitPortal::OnOverlapBegin);
    Trigger->OnComponentEndOverlap.AddDynamic(this, &AExitPortal::OnOverlapEnd);

    if (ChargeWidgetComp)
        ChargeWidgetComp->InitWidget();
}

void AExitPortal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bCharging) TickCharge(DeltaTime);
}

void AExitPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (bTriggered) return;
    APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
    if (!Player) return;

    bPlayerOnPad = true;
    bCharging = true;   // ticking resumes; ChargeElapsed keeps its current value

    if (ChargeWidgetComp)
        ChargeWidgetComp->SetVisibility(true);

    // Start (or restart) the looping charge sound
    if (ChargeSound && !ChargeAudio)
    {
        ChargeAudio = UGameplayStatics::SpawnSoundAttached(
            ChargeSound, RootComponent);
        // If the sound asset isn't already looping, you can loop via the cue/asset settings.
    }
    else if (ChargeAudio && !ChargeAudio->IsPlaying())
    {
        ChargeAudio->Play();
    }
}

void AExitPortal::TickCharge(float DeltaTime)
{
    if (bPlayerOnPad)
    {
        // Filling up
        ChargeElapsed += DeltaTime;
    }
    else
    {
        // Draining back down
        ChargeElapsed -= DeltaTime * DrainRate;
    }

    ChargeElapsed = FMath::Clamp(ChargeElapsed, 0.f, TravelDelay);
    float Percent = FMath::Clamp(ChargeElapsed / TravelDelay, 0.f, 1.f);

    // Drive the radial widget
    if (ChargeWidgetComp)
        if (UPortalChargeWidget* W = Cast<UPortalChargeWidget>(ChargeWidgetComp->GetUserWidgetObject()))
            W->SetPercent(Percent);

    // Fully charged → travel
    if (Percent >= 1.f)
    {
        bCharging = false;
        TriggerLevelLoad();
        return;
    }

    // Fully drained AND player is off → stop ticking and hide the bar
    if (Percent <= 0.f && !bPlayerOnPad)
    {
        bCharging = false;
        if (ChargeWidgetComp)
            ChargeWidgetComp->SetVisibility(false);
    }
}

void AExitPortal::TriggerLevelLoad()
{
    bCharging = false;
    bTriggered = true;   // lock it so re-overlap during travel does nothing

    if (ChargeWidgetComp)
        ChargeWidgetComp->SetVisibility(false);

    if (ChargeAudio)
    {
        ChargeAudio->Stop();
        ChargeAudio = nullptr;
    }

    UTheHuntGameInstance* GI = Cast<UTheHuntGameInstance>(GetGameInstance());
    if (!GI) return;
    GI->TransitionToLevel(LevelToLoad);
}

void AExitPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (bTriggered) return;
    if (!Cast<APlayerCharacter>(OtherActor)) return;

    bPlayerOnPad = false;
    // Keep bCharging true so TickCharge keeps running to DRAIN it down.
    // It only stops ticking once it drains fully to 0 (handled in TickCharge).

    if (ChargeAudio && ChargeAudio->IsPlaying())
        ChargeAudio->Stop();
}