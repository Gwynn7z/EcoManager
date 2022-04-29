#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "StructHandler.h"
#include "Components/ProgressBar.h"
#include "Bars.generated.h"


UCLASS()
class ECOMANAGER_API UBars : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void SetBarValue(TMap<EStats, int32> NewStats) const;

protected:
	UPROPERTY(meta = (BindWidget)) UProgressBar* MoneyBar;
	UPROPERTY(meta = (BindWidget)) UProgressBar* LikeBar;
	UPROPERTY(meta = (BindWidget)) UProgressBar* EcoBar;
	UPROPERTY(meta = (BindWidget)) UProgressBar* EnergyBar;

	UPROPERTY(meta = (BindWidget)) UImage* MoneyImage;
	UPROPERTY(meta = (BindWidget)) UImage* LikeImage;
	UPROPERTY(meta = (BindWidget)) UImage* EcoImage;
	UPROPERTY(meta = (BindWidget)) UImage* EnergyImage;
};
