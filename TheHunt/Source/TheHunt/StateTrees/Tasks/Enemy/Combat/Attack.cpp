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

    UE_LOG(LogTemp, Warning, TEXT("FAttack EnterState called"));

    if (!InstanceData.AbilitySystemComponent)
    {
        UE_LOG(LogTemp, Error, TEXT("FAttack: ASC is NULL"));
        return EStateTreeRunStatus::Failed;
    }

    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Slash")));
    InstanceData.AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAttack::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (InstanceData.AbilitySystemComponent->HasMatchingGameplayTag(
        FGameplayTag::RequestGameplayTag("State.Staggered")))
    {
        FGameplayTagContainer TagContainer;
        TagContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Attack.Slash"));
        InstanceData.AbilitySystemComponent->CancelAbilities(&TagContainer);

        return EStateTreeRunStatus::Failed;
    }

    // Ability finished if no instance of it is still active
    FGameplayTagContainer Query;
    Query.AddTag(FGameplayTag::RequestGameplayTag("Ability.Attack.Slash"));
    TArray<FGameplayAbilitySpec*> Specs;
    InstanceData.AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(Query, Specs);

    bool bStillActive = false;
    for (FGameplayAbilitySpec* Spec : Specs)
    {
        if (Spec->IsActive()) { bStillActive = true; break; }
    }

    if (!bStillActive)
    {
        return EStateTreeRunStatus::Succeeded;
    }

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
