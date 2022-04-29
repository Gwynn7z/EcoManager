
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ManagerHUD.generated.h"

UCLASS()
class ECOMANAGER_API AManagerHUD : public AHUD
{
	GENERATED_BODY()

	
public:
	AManagerHUD();
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly)  UTexture2D* Pointer;
};
