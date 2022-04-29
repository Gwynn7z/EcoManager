#include "SettingsPanelWidget.h"

void USettingsPanelWidget::SetGraphicText(FText Text) const
{
	GraphicText->SetText(Text);
}

void USettingsPanelWidget::SetResetGameEnable(bool bEnabled)
{
	bEnabledReset = bEnabled;
}

void USettingsPanelWidget::SetLoadGameEnabled(bool bEnabled)
{
	bEnabledLoad = bEnabled;
}

void USettingsPanelWidget::HoverLoadGame() const
{
	LoadGameText->SetColorAndOpacity(FSlateColor(FColor::Red));	
}

void USettingsPanelWidget::UnHoverLoadGame() const
{
	if(bEnabledLoad) LoadGameText->SetColorAndOpacity(FSlateColor(FColor::White));
	else LoadGameText->SetColorAndOpacity(FSlateColor(FColor::Black));	
}

void USettingsPanelWidget::HoverResetGame() const
{
	ResetGameText->SetColorAndOpacity(FSlateColor(FColor::Red));	
}

void USettingsPanelWidget::UnHoverResetGame() const
{
	if(bEnabledReset) ResetGameText->SetColorAndOpacity(FSlateColor(FColor::White));
	else ResetGameText->SetColorAndOpacity(FSlateColor(FColor::Black));	
}
