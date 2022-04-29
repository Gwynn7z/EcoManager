#include "QuestionPanelWidget.h"
#include "Components/TextBlock.h"

void  UQuestionPanelWidget::SendQuestion(FText Text, FText LeftChoice, FText RightChoice) const
{
	MainText->SetText(Text);
	RightText->SetText(RightChoice);
	LeftText->SetText(LeftChoice);
}

void UQuestionPanelWidget::SendConsequence(FText Text) const
{
	MainText->SetText(Text);
};