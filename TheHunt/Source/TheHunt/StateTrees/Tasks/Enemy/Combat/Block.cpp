// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Tasks/Enemy/Combat/Block.h"

#include "GameplayAbilitySystem/Abilities/BasicBlockingAbility.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FBlock::EnterState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.AbilitySystemComponent)
        return EStateTreeRunStatus::Failed;

    InstanceData.bAbilityEnded = false;
    InstanceData.bExitRequested = false;
    InstanceData.TimeInState = 0.f;
    InstanceData.TargetDuration = FMath::FRandRange(InstanceData.MinDuration, InstanceData.MaxDuration);

    // Bind before activating so we don't miss a fast-ending ability
    InstanceData.AbilityEndedHandle = InstanceData.AbilitySystemComponent->OnAbilityEnded.AddLambda(
        [&InstanceData](const FAbilityEndedData& Data)
        {
            if (Data.AbilityThatEnded->AbilityTags.HasTag(
                FGameplayTag::RequestGameplayTag(FName("Ability.Block"))))
            {
                InstanceData.bAbilityEnded = true;
            }
        });

    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Block")));
    InstanceData.AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FBlock::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    // Ability already fully ended (either from our request or guard break)
    if (InstanceData.bAbilityEnded)
        return EStateTreeRunStatus::Succeeded;

    InstanceData.TimeInState += DeltaTime;

    if (InstanceData.Character->SetStagger())
        return EStateTreeRunStatus::Failed;

    // Duration expired — request the ability to play its exit animation
    if (!InstanceData.bExitRequested && InstanceData.TimeInState >= InstanceData.TargetDuration)
    {
        InstanceData.bExitRequested = true;

        FGameplayTagContainer BlockTag;
        BlockTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Block"));

        TArray<FGameplayAbilitySpec*> MatchingSpecs;
        InstanceData.AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(BlockTag, MatchingSpecs);

        for (FGameplayAbilitySpec* Spec : MatchingSpecs)
        {
            if (Spec->IsActive())
            {
                UBasicBlockingAbility* BlockAbility = Cast<UBasicBlockingAbility>(Spec->GetPrimaryInstance());
                if (BlockAbility)
                {
                    BlockAbility->RequestBlockExit();
                    break;
                }
            }
        }
    }

    return EStateTreeRunStatus::Running;
}

void FBlock::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    // Always unbind on exit to avoid dangling delegate
    if (InstanceData.AbilitySystemComponent && InstanceData.AbilityEndedHandle.IsValid())
    {
        InstanceData.AbilitySystemComponent->OnAbilityEnded.Remove(InstanceData.AbilityEndedHandle);
        InstanceData.AbilityEndedHandle.Reset();
    }

    // If we're exiting the state but the ability hasn't ended yet (e.g. StateTree forced a transition),
    // cancel it through GAS as a fallback
    if (!InstanceData.bAbilityEnded && InstanceData.AbilitySystemComponent)
    {
        FGameplayTagContainer BlockTag;
        BlockTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Block"));
        InstanceData.AbilitySystemComponent->CancelAbilities(&BlockTag);
    }
}