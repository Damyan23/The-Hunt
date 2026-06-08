#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HoverText.generated.h"

// Delegate declarations (dynamic multicast so they're bindable in Blueprint)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoverTextClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoverTextHoverStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoverTextHoverEnd);

UCLASS()
class UHoverText : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* Label;

    // ---- Events you can subscribe to ----
    UPROPERTY(BlueprintAssignable, Category = "Hover|Events")
    FOnHoverTextClicked OnClicked;

    UPROPERTY(BlueprintAssignable, Category = "Hover|Events")
    FOnHoverTextHoverStart OnHoverStart;

    UPROPERTY(BlueprintAssignable, Category = "Hover|Events")
    FOnHoverTextHoverEnd OnHoverEnd;

    // ---- The text itself ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Text")
    FText DisplayText = FText::FromString("Button");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Text")
    FSlateFontInfo FontInfo;

    // ---- Default (resting) state ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Default")
    float DefaultSize = 18.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Default")
    FLinearColor DefaultColor = FLinearColor::White;

    // ---- Hovered state ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Hovered")
    float HoverSize = 24.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Hovered")
    FLinearColor HoverColor = FLinearColor::Yellow;

    // ---- Clicked state ----
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Clicked")
    float ClickedSize = 22.f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover|Clicked")
    FLinearColor ClickedColor = FLinearColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hover")
    float InterpSpeed = 10.f;

protected:
    virtual void NativePreConstruct() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
    float CurrentSize = 18.f;
    float TargetSize = 18.f;
    FLinearColor CurrentColor = FLinearColor::White;
    FLinearColor TargetColor = FLinearColor::White;
    bool bIsHovered = false;
    bool bIsPressed = false;
};