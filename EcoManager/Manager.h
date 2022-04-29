#pragma once

#include "CoreMinimal.h"
#include "SettingsPanel.h"
#include "TipsPanel.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Manager.generated.h"

class ADesk;

UCLASS()
class ECOMANAGER_API AManager : public APawn
{
	GENERATED_BODY()

public:
	AManager();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere) USceneComponent* Root;
	UPROPERTY(EditAnywhere) UCameraComponent* Camera;
	
protected:
	virtual void BeginPlay() override;

private:
	void ChangeQuality() const;
	void Turn(float Value);
	void LookUp(float Value);
	void TurnMobile(float Value);
	void LookUpMobile(float Value);
	void Touch();

	TMap<int32, EGraphicSettings> GraphicSettings;
	int32 GraphicSetting;
	UPROPERTY() ADesk* PersonalDesk;
	UPROPERTY() ASettingsPanel* SettingsPanel;
	UPROPERTY() ATipsPanel* TipsPanel;
};
