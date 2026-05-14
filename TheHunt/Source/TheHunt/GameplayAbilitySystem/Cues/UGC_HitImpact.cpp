// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Cues/UGC_HitImpact.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

bool UGC_HitImpact::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
    UE_LOG(LogTemp, Warning, TEXT("GC_HitImpact executed"));
    UNiagaraSystem* VFX = const_cast<UNiagaraSystem*>(Cast<UNiagaraSystem>(Parameters.SourceObject.Get()));
    if (!VFX)
    {
        UE_LOG(LogTemp, Error, TEXT("VFX is NULL - SourceObject is: %s"),
            Parameters.SourceObject.Get() ? *Parameters.SourceObject.Get()->GetName() : TEXT("nullptr"));
        return true;
    }
    UE_LOG(LogTemp, Warning, TEXT("Spawning VFX: %s at %s"), *VFX->GetName(), *Parameters.Location.ToString());
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        MyTarget->GetWorld(),
        VFX,
        Parameters.Location,
        FRotator::ZeroRotator,
        FVector(10.f),
        true
    );
    return true;
}
