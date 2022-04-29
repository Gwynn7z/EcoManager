#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestionPanelWidget.generated.h"

class UTextBlock;

UCLASS()
class ECOMANAGER_API UQuestionPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION() void SendQuestion(FText Text, FText LeftChoice, FText RightChoice) const;
	UFUNCTION() void SendConsequence(FText Text) const;

protected:
	UPROPERTY(meta = (BindWidget)) UTextBlock* MainText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* LeftText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* RightText;
	
};
