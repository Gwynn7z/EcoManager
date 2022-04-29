#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "StructHandler.h"
#include "RightScreen.generated.h"

UCLASS()
class ECOMANAGER_API URightScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void SetFlagImage(UTexture2D* TextureFlag) const;

	UFUNCTION() void SetBarValue(TMap<EStats, int32> NewStats) const;

protected:
	UPROPERTY(meta = (BindWidget)) UProgressBar* SafetyBar;
	UPROPERTY(meta = (BindWidget)) UProgressBar* InstructionBar;
	UPROPERTY(meta = (BindWidget)) UProgressBar* ResearchBar;
	UPROPERTY(meta = (BindWidget)) UProgressBar* GreenSpaceBar;
	
	UPROPERTY(meta = (BindWidget)) UImage* FlagImage;
	
};
