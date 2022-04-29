#pragma once

#include "CoreMinimal.h"

#include "QuestionPanelWidget.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "QuestionPanel.generated.h"

UCLASS()
class ECOMANAGER_API AQuestionPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuestionPanel();

	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere) UWidgetComponent* TextWidgetComponent;
	
	UFUNCTION() void SendQuestion(FText Text, FText LeftChoice, FText RightChoice) const;
	UFUNCTION() void SendConsequence(FText Text) const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY() UQuestionPanelWidget* TextWidget;
	
};
