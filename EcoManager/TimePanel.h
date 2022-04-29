#pragma once

#include "CoreMinimal.h"
#include "TimePanelWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "TimePanel.generated.h"

UCLASS()
class ECOMANAGER_API ATimePanel : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimePanel();

	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere) UWidgetComponent* TimeWidgetComponent;
	
	UFUNCTION() void SetTime(FText Text) const;
	UFUNCTION() void SetText(FText NewText, FColor NewColor) const;
	UFUNCTION() void SetColor(FColor Color) const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY() UTimePanelWidget* TimeWidget;

};
