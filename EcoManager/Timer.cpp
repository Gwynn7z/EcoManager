#include "Timer.h"
#include "Components/TextBlock.h"

void UTimer::SetText(FText Text) const
{
	TextItem->SetText(Text);
}

void UTimer::SetHover(bool bHover) const
{
	FColor Color = FColor::White;
	if(TextItem->GetText().EqualTo(FText::FromString("Fatto"))) Color = FColor::Green;
	if(bHover) Color = FColor::FromHex("FF4600FF");
	const FSlateColor SlateColor = FSlateColor(Color);
	TextItem->SetColorAndOpacity(SlateColor);
}
