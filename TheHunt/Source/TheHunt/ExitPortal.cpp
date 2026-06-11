#include "ExitPortal.h"
#include "Kismet/GameplayStatics.h"
#include "InputPlayer/PlayerCharacter.h"   // adjust to your APlayerCharacter path
#include "TheHuntGameInstance.h"

void AExitPortal::OnInteract_Implementation(AActor* Interactor)
{
    Super::OnInteract_Implementation(Interactor);

    APlayerCharacter* Player = Cast<APlayerCharacter>(
        UGameplayStatics::GetPlayerCharacter(this, 0));

    if (Player)
    {
        if (UTheHuntGameInstance* GI = GetGameInstance<UTheHuntGameInstance>())
        {
            GI->StoreProgression(Player->GatherProgression());
        }
    }

    UGameplayStatics::OpenLevel(this, "Lvl_Map");
}