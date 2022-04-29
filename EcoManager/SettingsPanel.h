#pragma once

#include "CoreMinimal.h"
#include "SettingsPanelWidget.h"
#include "StructHandler.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "SettingsPanel.generated.h"

UCLASS()
class ECOMANAGER_API ASettingsPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASettingsPanel();

	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere) UBoxComponent* LeftArrowBox;
	UPROPERTY(EditAnywhere) UBoxComponent* RightArrowBox;

	UPROPERTY(EditAnywhere) UBoxComponent* LoadGameBox;
	UPROPERTY(EditAnywhere) UBoxComponent* ResetGameBox;
	
	UPROPERTY(EditAnywhere) UWidgetComponent* SettingsWidgetComponent;

	UFUNCTION() void SetGraphicText(FText Text) const;
	UFUNCTION() void HoverArrow(EWay ArrowWay) const;
	UFUNCTION() void UnHoverArrow(EWay ArrowWay) const;
	UFUNCTION() void HoverLoadGame() const;
	UFUNCTION() void UnHoverLoadGame() const;
	UFUNCTION() void HoverResetGame() const;
	UFUNCTION() void UnHoverResetGame() const;
	UFUNCTION() void SetResetGameEnable(bool bEnabled) const;
	UFUNCTION() void SetLoadGameEnabled(bool bEnabled) const;

protected:
	virtual void BeginPlay() override;
	

	UPROPERTY() USettingsPanelWidget* SettingsWidget;

};
