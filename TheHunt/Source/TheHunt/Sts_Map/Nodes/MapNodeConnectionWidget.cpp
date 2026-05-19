// Fill out your copyright notice in the Description page of Project Settings.


#include "MapNodeConnectionWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"

int32 UMapNodeConnectionsWidget::NativePaint(
    const FPaintArgs& Args,
    const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect,
    FSlateWindowElementList& OutDrawElements,
    int32 LayerId,
    const FWidgetStyle& InWidgetStyle,
    bool bParentEnabled) const
{
    int32 Layer = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    APlayerController* PC = GetOwningPlayer();
    if (!PC) return Layer;

    for (AMapNode* Node : MapNodes)
    {
        if (!Node) continue;

        for (AMapNode* NextNode : Node->NextNodes)
        {
            if (!NextNode) continue;

            // Convert world positions to screen space
            FVector2D StartScreen, EndScreen;
            bool bStartValid = PC->ProjectWorldLocationToScreen(Node->GetActorLocation(), StartScreen);
            bool bEndValid = PC->ProjectWorldLocationToScreen(NextNode->GetActorLocation(), EndScreen);

            if (!bStartValid || !bEndValid) continue;

            // Convert screen pos to local widget space
            FVector2D LocalStart = StartScreen / UWidgetLayoutLibrary::GetViewportScale(this);
            FVector2D LocalEnd = EndScreen / UWidgetLayoutLibrary::GetViewportScale(this);

            // Draw dashed line
            FVector2D Dir = (LocalEnd - LocalStart);
            float TotalLength = Dir.Size();
            Dir.Normalize();

            float DashLength = 15.f;
            float GapLength = 10.f;
            float CurrentDist = 0.f;

            while (CurrentDist < TotalLength)
            {
                float DashEnd = FMath::Min(CurrentDist + DashLength, TotalLength);

                FVector2D DashStart2D = LocalStart + Dir * CurrentDist;
                FVector2D DashEnd2D = LocalStart + Dir * DashEnd;

                TArray<FVector2D> Points = { DashStart2D, DashEnd2D };

                FSlateDrawElement::MakeLines(
                    OutDrawElements,
                    Layer,
                    AllottedGeometry.ToPaintGeometry(),
                    Points,
                    ESlateDrawEffect::None,
                    FLinearColor::White,
                    true,
                    3.f // thickness
                );

                CurrentDist += DashLength + GapLength;
            }

            // Draw arrowhead at the end
            FVector2D ArrowTip = LocalEnd;
            FVector2D Perp = FVector2D(-Dir.Y, Dir.X);
            float ArrowSize = 10.f;

            TArray<FVector2D> ArrowPoints = {
                ArrowTip,
                ArrowTip - Dir * ArrowSize + Perp * ArrowSize * 0.5f,
                ArrowTip - Dir * ArrowSize - Perp * ArrowSize * 0.5f,
                ArrowTip
            };

            FSlateDrawElement::MakeLines(
                OutDrawElements,
                Layer,
                AllottedGeometry.ToPaintGeometry(),
                ArrowPoints,
                ESlateDrawEffect::None,
                FLinearColor::White,
                true,
                3.f
            );
        }
    }

    return Layer;
}