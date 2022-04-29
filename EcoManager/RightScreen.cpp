#include "RightScreen.h"

void URightScreen::SetFlagImage(UTexture2D* TextureFlag) const
{
	FlagImage->SetBrushFromTexture(TextureFlag);
}

void URightScreen::SetBarValue(TMap<EStats, int32> NewStats) const
{
	for(auto &Stat : NewStats)
	{
		const float Value = static_cast<float>(Stat.Value) / 100;
		switch(Stat.Key)
		{
		case EStats::Safety:
			SafetyBar->SetPercent(Value);
			break;
		case EStats::Research:
			ResearchBar->SetPercent(Value);
			break;
		case EStats::Instruction:
			InstructionBar->SetPercent(Value);
			break;
		case EStats::GreenSpace:
			GreenSpaceBar->SetPercent(Value);
			break;
		default:
			break;
		}
	}
}
