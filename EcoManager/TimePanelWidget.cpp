#include "TimePanelWidget.h"

void UTimePanelWidget::SetTime(FText Text) const
{
	Time->SetText(Text);
}

void UTimePanelWidget::SetTextColor(FColor Color) const
{
	Time->SetColorAndOpacity(FSlateColor(Color));
}

void UTimePanelWidget::SetText(FText NewText, FColor NewColor) const
{
	MonthText->SetText(NewText);
	MonthText->SetColorAndOpacity(FSlateColor(NewColor));
}