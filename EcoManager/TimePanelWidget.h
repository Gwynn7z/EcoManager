#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TimePanelWidget.generated.h"


UCLASS()
class ECOMANAGER_API UTimePanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void SetTime(FText Text) const;
	UFUNCTION() void SetText(FText NewText, FColor NewColor) const;
	UFUNCTION() void SetTextColor(FColor Color) const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* Time;
	UPROPERTY(meta = (BindWidget)) UTextBlock* MonthText;
};
