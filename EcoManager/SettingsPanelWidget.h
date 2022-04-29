#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SettingsPanelWidget.generated.h"


UCLASS()
class ECOMANAGER_API USettingsPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void SetGraphicText(FText Text) const;

	UFUNCTION() void HoverLoadGame() const;
	UFUNCTION() void UnHoverLoadGame() const;

	UFUNCTION() void HoverResetGame() const;
	UFUNCTION() void UnHoverResetGame() const;
	
	
	UFUNCTION() void SetResetGameEnable(bool bEnabled);
	UFUNCTION() void SetLoadGameEnabled(bool bEnabled);

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* GraphicText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* ResetGameText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* LoadGameText;

private:
	bool bEnabledReset;
	bool bEnabledLoad;
};
