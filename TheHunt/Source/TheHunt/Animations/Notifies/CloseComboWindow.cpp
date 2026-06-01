// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/Notifies/CloseComboWindow.h"

#include "GameplayAbilitySystem/BasicAttackAbility.h"
#include "InputPlayer/PlayerCharacter.h"

void UCloseComboWindow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                               const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
    if (!Player) return;

    for (FGameplayAbilitySpec& Spec : Player->AbilitySystemComponent->GetActivatableAbilities())
    {
        for (UGameplayAbility* Instance : Spec.GetAbilityInstances())
        {
            
            UBasicAttackAbility* Attack = Cast<UBasicAttackAbility>(Instance);
            if (Attack && Attack->IsActive())
            {
                UE_LOG(LogTemp, Warning, TEXT("goes in here"));
                Attack->CloseComboWindow(); // closes window
                // If queued, trigger next attack right now
                if (Attack->bNextAttackQueued)
                    Attack->TriggerNextAttack();
                return;
            }
        }
    }
}
