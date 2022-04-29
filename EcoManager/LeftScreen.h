#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeftScreen.generated.h"

class UTextBlock;

UCLASS()
class ECOMANAGER_API ULeftScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION() void SetCountry(FText NewCountryName) const;
	UFUNCTION() void SetInfos(FText NewInfos) const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* CountryName;
	UPROPERTY(meta = (BindWidget)) UTextBlock* Infos;
};
