// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Tasks/Enemy/Combat/Attack.h"

#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FAttack::EnterState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FStateTreeTaskCommonBase::EnterState(Context, Transition);
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.AbilitySystemComponent)
        return EStateTreeRunStatus::Failed;

    InstanceData.bAbilityEnded = false;

    // Bind before activating so we don't miss a fast-ending ability
    InstanceData.AbilityEndedHandle = InstanceData.AbilitySystemComponent->OnAbilityEnded.AddLambda(
        [&InstanceData](const FAbilityEndedData& Data)
        {
            if (Data.AbilityThatEnded->AbilityTags.HasTag(
                FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Slash"))))
            {
                InstanceData.bAbilityEnded = true;
            }
        });

    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Slash")));
    InstanceData.AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAttack::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    // If enemy got staggered during attack, fail immediately
    if (InstanceData.AbilitySystemComponent->HasMatchingGameplayTag(
        FGameplayTag::RequestGameplayTag("State.Staggered")))
    {
        // Cancel the attack ability
        FGameplayTagContainer TagContainer;
        TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Attack.Slash"));
        InstanceData.AbilitySystemComponent->CancelAbilities(&TagContainer);

        return EStateTreeRunStatus::Failed;
    }

    if (InstanceData.bAbilityEnded)
        return EStateTreeRunStatus::Succeeded;

    return EStateTreeRunStatus::Running;
}

void FAttack::ExitState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FStateTreeTaskCommonBase::ExitState(Context, Transition);
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    // Always unbind on exit to avoid dangling delegate
    if (InstanceData.AbilitySystemComponent && InstanceData.AbilityEndedHandle.IsValid())
    {
        InstanceData.AbilitySystemComponent->OnAbilityEnded.Remove(InstanceData.AbilityEndedHandle);
    }
}
