// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/TransitionWidget.h"

void UTransitionWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (DissolveImage)
    {
        // Create a dynamic instance from whatever material is on the image brush
        DissolveMID = DissolveImage->GetDynamicMaterial();
        // GetDynamicMaterial() creates one from the brush material if not already dynamic
    }
}

void UTransitionWidget::PlayDissolve(float From, float To, float Duration)
{
    DissolveStart = From;
    DissolveEnd = To;
    DissolveDuration = FMath::Max(Duration, 0.0001f);
    DissolveElapsed = 0.f;
    bDissolving = true;

    if (DissolveMID)
        DissolveMID->SetScalarParameterValue(FName("DissolveAmount"), From);
}

void UTransitionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!bDissolving || !DissolveMID) return;

    DissolveElapsed += InDeltaTime;
    float Alpha = FMath::Clamp(DissolveElapsed / DissolveDuration, 0.f, 1.f);

    float Value = FMath::Lerp(DissolveStart, DissolveEnd, Alpha);
    DissolveMID->SetScalarParameterValue(FName("DissolveAmount"), Value);

    if (Alpha >= 1.f)
    {
        bDissolving = false; // done
    }
}