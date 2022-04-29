#include "Bars.h"


void UBars::SetBarValue(TMap<EStats, int32> NewStats) const
{
	for(auto &Stat : NewStats)
	{
		const float Value = static_cast<float>(Stat.Value) / 100;
		switch(Stat.Key)
		{
		case EStats::Eco:
			EcoBar->SetPercent(Value);
			break;
		case EStats::Energy:
			EnergyBar->SetPercent(Value);
			break;
		case EStats::Like:
			LikeBar->SetPercent(Value);
			break;
		case EStats::Money:
			MoneyBar->SetPercent(Value);
			break;
		default:
			break;
		}
	}
}
