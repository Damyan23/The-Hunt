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

    InstanceData.TimeInState = 0.f;

    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Attack.Slash")));
    InstanceData.AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FAttack::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    InstanceData.TimeInState += DeltaTime;

    // Keep rotating toward target during the wind-up window
    if (InstanceData.TimeInState <= InstanceData.RotateTrackDuration
        && InstanceData.Character && InstanceData.TargetActor)
    {
        FVector ToTarget = InstanceData.TargetActor->GetActorLocation() - InstanceData.Character->GetActorLocation();
        ToTarget.Z = 0.f;
        if (!ToTarget.IsNearlyZero())
        {
            FRotator TargetRot = ToTarget.Rotation();
            FRotator CurrentRot = InstanceData.Character->GetActorRotation();
            FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, InstanceData.RotationSpeed);
            NewRot.Pitch = 0.f;
            NewRot.Roll = 0.f;
            InstanceData.Character->SetActorRotation(NewRot);
        }
    }

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
