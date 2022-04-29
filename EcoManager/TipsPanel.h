#pragma once

#include "CoreMinimal.h"
#include "StructHandler.h"
#include "TipsPanelWidget.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "TipsPanel.generated.h"

UCLASS()
class ECOMANAGER_API ATipsPanel : public AActor
{
	GENERATED_BODY()
public:	
    ATipsPanel();

    UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;
    UPROPERTY(EditAnywhere) UWidgetComponent* TipsWidgetComponent;
	UPROPERTY(EditAnywhere) UBoxComponent* LeftArrowBox;
	UPROPERTY(EditAnywhere) UBoxComponent* RightArrowBox;
	UPROPERTY(EditAnywhere) UBoxComponent* ToggleMenuBox;

	UFUNCTION() void SetCurrentSuggestions(TArray<EPowerPlants> Suggestions);
	UFUNCTION() void ToggleMenuType();
	UFUNCTION() void ClickArrow(EWay Way);
	UFUNCTION() void HoverArrow(EWay ArrowWay) const;
	UFUNCTION() void UnHoverArrow(EWay ArrowWay) const;
	UFUNCTION() void HoverChangeMenu() const;
	UFUNCTION() void UnHoverChangeMenu() const;
	UFUNCTION() void SetInfosPanel();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* RulesData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* PowerPlantsTipsData;

protected:
    virtual void BeginPlay() override;

    UPROPERTY() UTipsPanelWidget* TipsWidget;

	TArray<UTexture2D*> RulesTextures;
	TMap<EPowerPlants, TArray<UTexture2D*>> SuggestionTextures;
	EShowingMenuType CurrentMenu;

	int32 CurrentRulesIndex = 0;
	int32 CurrentSuggestionsIndex = 0;
	TArray<UTexture2D*> CurrentSuggestions;

	TArray<FPowerPlantsTips*> PowerPlantsTipsDB;
	TArray<FRulesTextures*> RulesTexturesDB;

private:
	UPROPERTY() UTexture2D* Legenda;
	

};
