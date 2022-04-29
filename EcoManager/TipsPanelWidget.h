#pragma once

#include "CoreMinimal.h"
#include "StructHandler.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TipsPanelWidget.generated.h"


UCLASS()
class ECOMANAGER_API UTipsPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void SetChangeMenu(FText NewText) const;
	UFUNCTION() void SetCurrentImage(UTexture2D* NewTexture) const;
	UFUNCTION() void HoverChangeMenu() const;
	UFUNCTION() void UnHoverChangeMenu() const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* ChangeMenuText;
	UPROPERTY(meta = (BindWidget)) UImage* CurrentImage;
};
