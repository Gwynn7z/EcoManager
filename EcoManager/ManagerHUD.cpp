
#include "ManagerHUD.h"
#include "CanvasItem.h"
#include "Manager.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Canvas.h"

AManagerHUD::AManagerHUD() {
	static ConstructorHelpers::FObjectFinder<UTexture2D> PointerAsset(TEXT("Texture2D'/Game/Images/Pointer.Pointer'"));

	if (PointerAsset.Object != NULL)
	{
		Pointer = PointerAsset.Object;
	}
}

void AManagerHUD::DrawHUD()
{
	Super::DrawHUD();

	if (Pointer)
	{
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		FVector2D CrossHairDrawPosition(Center.X - (Pointer->GetSurfaceWidth() * 0.5f), Center.Y - (Pointer->GetSurfaceHeight() * 0.5f));
		FCanvasTileItem TileItem(CrossHairDrawPosition, Pointer->GetResource(), FVector2D(25.f, 25.f), FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (Pawn) {
			AManager* Manager = Cast<AManager>(Pawn);
			if (Manager) Canvas->DrawItem(TileItem);
		}
	}
}