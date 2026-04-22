#include "StateTrees/Tasks/Enemy/Stagger.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FStagger::EnterState(FStateTreeExecutionContext& Context,
    const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    InstanceData.ElapsedTime = 0.f;
    InstanceData.bPlayingExit = false;
    InstanceData.bBlockReactionDone = false;
    InstanceData.ExitElapsedTime = 0.f;

    if (InstanceData.StaggerExitMontage)
    {
        InstanceData.StaggerExitDuration = InstanceData.StaggerExitMontage->GetPlayLength();
    }
    else
    {
        InstanceData.StaggerExitDuration = 0.f;
    }

    if (InstanceData.Character)
    {
        InstanceData.Character->BaseAttributes->SetStagger(0);

        if (InstanceData.BlockReactionMontage)
        {
            InstanceData.Character->PlayAnimMontage(InstanceData.BlockReactionMontage);
        }
        else
        {
            InstanceData.bBlockReactionDone = true;

            if (InstanceData.StaggerMontage)
            {
                InstanceData.Character->PlayAnimMontage(InstanceData.StaggerMontage);
            }
        }
    }

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStagger::Tick(FStateTreeExecutionContext& Context, float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

    if (!InstanceData.Character)
        return EStateTreeRunStatus::Failed;

    UAnimInstance* AnimInstance = InstanceData.Character->GetMesh()->GetAnimInstance();
    if (!AnimInstance)
        return EStateTreeRunStatus::Failed;

    // -------------------------
    // Phase 1 — Block reaction
    // -------------------------
    if (!InstanceData.bBlockReactionDone)
    {
        if (!InstanceData.BlockReactionMontage ||
            !AnimInstance->Montage_IsPlaying(InstanceData.BlockReactionMontage))
        {
            InstanceData.bBlockReactionDone = true;
            InstanceData.ElapsedTime = 0.f;

            if (InstanceData.StaggerMontage)
            {
                InstanceData.Character->PlayAnimMontage(InstanceData.StaggerMontage);
            }
        }

        return EStateTreeRunStatus::Running;
    }

    // -------------------------
    // Phase 2 — Stagger hold
    // -------------------------
    InstanceData.ElapsedTime += DeltaTime;

    const float ExitStartTime = FMath::Max(
        0.f,
        InstanceData.StaggerDuration - InstanceData.StaggerExitDuration
    );

    if (!InstanceData.bPlayingExit &&
        InstanceData.StaggerExitMontage &&
        InstanceData.ElapsedTime >= ExitStartTime)
    {
        InstanceData.bPlayingExit = true;
        InstanceData.Character->PlayAnimMontage(InstanceData.StaggerExitMontage);
    }

    // -------------------------
    // Phase 3 — End stagger
    // -------------------------
    if (InstanceData.ElapsedTime >= InstanceData.StaggerDuration)
    {
        InstanceData.AbilitySystemComponent->RemoveLooseGameplayTags(
            FGameplayTagContainer(
                FGameplayTag::RequestGameplayTag("State.Staggered")
            )
        );

        return EStateTreeRunStatus::Succeeded;
    }

    return EStateTreeRunStatus::Running;
}