#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "Timer.generated.h"

UCLASS()
class ECOMANAGER_API UTimer : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void SetText(FText Text) const;
	UFUNCTION() void SetHover(bool bHover) const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextItem;
	
};
