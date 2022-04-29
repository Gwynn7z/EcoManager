#include "LeftScreen.h"
#include "Components/TextBlock.h"

void ULeftScreen::SetCountry(FText NewCountryName) const
{
	FSlateFontInfo Font = CountryName->Font;
	Font.Size = 35;
    if(NewCountryName.ToString().Equals("Lussemburgo")) Font.Size = 28;
	CountryName->SetFont(Font);
	
	CountryName->SetText(NewCountryName);
}

void ULeftScreen::SetInfos(FText NewInfos) const
{
	Infos->SetText(NewInfos);
}