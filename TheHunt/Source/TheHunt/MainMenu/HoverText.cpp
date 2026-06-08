#include "HoverText.h"

void UHoverText::NativePreConstruct()
{
    Super::NativePreConstruct();
    if (!Label) return;
    Label->SetText(DisplayText);
}

void UHoverText::NativeConstruct()
{
    Super::NativeConstruct();
    if (Label) Label->SetText(DisplayText);
    CurrentSize = TargetSize = DefaultSize;
    CurrentColor = TargetColor = DefaultColor;
}

void UHoverText::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
    bIsHovered = true;
    if (!bIsPressed) { TargetSize = HoverSize; TargetColor = HoverColor; }
    OnHoverStart.Broadcast();
}

void UHoverText::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);
    bIsHovered = false;
    bIsPressed = false;
    TargetSize = DefaultSize;
    TargetColor = DefaultColor;
    OnHoverEnd.Broadcast();
}

FReply UHoverText::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    bIsPressed = true;
    TargetSize = ClickedSize;
    TargetColor = ClickedColor;
    return FReply::Handled();
}

FReply UHoverText::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // Only count as a click if the press ends while still over the widget
    bool bWasPressed = bIsPressed;
    bIsPressed = false;

    TargetSize = bIsHovered ? HoverSize : DefaultSize;
    TargetColor = bIsHovered ? HoverColor : DefaultColor;

    if (bWasPressed && bIsHovered)
    {
        OnClicked.Broadcast();
    }
    return FReply::Handled();
}

void UHoverText::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (!Label) return;

    CurrentSize = FMath::FInterpTo(CurrentSize, TargetSize, InDeltaTime, InterpSpeed);
    CurrentColor = FMath::CInterpTo(CurrentColor, TargetColor, InDeltaTime, InterpSpeed);

    FSlateFontInfo Font = Label->GetFont();
    Font.Size = FMath::RoundToInt(CurrentSize);
    Label->SetFont(Font);
    Label->SetColorAndOpacity(FSlateColor(CurrentColor));
}