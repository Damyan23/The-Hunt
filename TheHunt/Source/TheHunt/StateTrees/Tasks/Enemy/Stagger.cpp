// Fill out your copyright notice in the Description page of Project Settings.


#include "StateTrees/Tasks/Enemy/Stagger.h"

#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FStagger::EnterState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
    InstanceData.ElapsedTime = 0.f;

    if (InstanceData.Character)
    {
        InstanceData.Character->PlayAnimMontage(InstanceData.StaggerMontage);
        InstanceData.Character->BaseAttributes->SetStagger(0);
        InstanceData.AbilitySystemComponent->AddLooseGameplayTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("State.Staggered")));
    }
    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStagger::Tick(FStateTreeExecutionContext& Context, float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);
    if (!InstanceData.Character) return EStateTreeRunStatus::Failed;

    UAnimInstance* AnimInstance = InstanceData.Character->GetMesh()->GetAnimInstance();

    InstanceData.ElapsedTime += DeltaTime;

    if (!InstanceData.bPlayingExit && InstanceData.ElapsedTime >= InstanceData.StaggerDuration)
    {
        // Jump to exit section
        AnimInstance->Montage_JumpToSection(FName("StaggerExit"), InstanceData.StaggerMontage);
        AnimInstance->Montage_SetPlayRate(AnimInstance->GetCurrentActiveMontage(),0.8f);
        InstanceData.bPlayingExit = true;
    }

    // Wait for exit section to finish
    if (InstanceData.bPlayingExit && !AnimInstance->Montage_IsPlaying(InstanceData.StaggerMontage))
    {
        InstanceData.AbilitySystemComponent->RemoveLooseGameplayTags(FGameplayTagContainer(FGameplayTag::RequestGameplayTag("State.Staggered")));
        return EStateTreeRunStatus::Succeeded;
    }

    return EStateTreeRunStatus::Running;
}
