#include "TipsPanelWidget.h"
#include "StructHandler.h"


void UTipsPanelWidget::SetChangeMenu(FText NewText) const
{
	ChangeMenuText->SetText(NewText);
}

void UTipsPanelWidget::SetCurrentImage(UTexture2D* NewTexture) const
{
	CurrentImage->SetBrushFromTexture(NewTexture);
}

void UTipsPanelWidget::HoverChangeMenu() const
{
	ChangeMenuText->SetColorAndOpacity(FSlateColor(FColor::Red));	
}

void UTipsPanelWidget::UnHoverChangeMenu() const
{
	ChangeMenuText->SetColorAndOpacity(FSlateColor(FColor::White));
}
