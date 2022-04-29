#include "Manager.h"
#include "Desk.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

AManager::AManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	GraphicSettings.Add(0, EGraphicSettings::Low);
	GraphicSettings.Add(1, EGraphicSettings::Medium);
	GraphicSettings.Add(2, EGraphicSettings::High);
	GraphicSettings.Add(3, EGraphicSettings::Epic);
	
	GraphicSetting = 1;
}

void AManager::BeginPlay()
{
	Super::BeginPlay();

	if(AActor* TempDesk = UGameplayStatics::GetActorOfClass(GetWorld(), ADesk::StaticClass())) PersonalDesk = Cast<ADesk>(TempDesk);

	if(AActor* SettingsPanelTemp = UGameplayStatics::GetActorOfClass(GetWorld(), ASettingsPanel::StaticClass())) SettingsPanel = Cast<ASettingsPanel>(SettingsPanelTemp);
	if(AActor* TipsPanelTemp = UGameplayStatics::GetActorOfClass(GetWorld(), ATipsPanel::StaticClass())) TipsPanel = Cast<ATipsPanel>(TipsPanelTemp);

	if(UGameplayStatics::DoesSaveGameExist(TEXT("DefaultSlot"),0)) SettingsPanel->SetLoadGameEnabled(true);
	else SettingsPanel->SetLoadGameEnabled(false);
	
	SettingsPanel->SetResetGameEnable(false);

	GEngine->GetGameUserSettings()->LoadSettings();
	GEngine->GetGameUserSettings()->SetFullscreenMode(EWindowMode::Fullscreen);
	GraphicSetting = GEngine->GetGameUserSettings()->GetTextureQuality();
	SettingsPanel->SetGraphicText(FText::FromString(GraphicQualityName[GraphicSettings[GraphicSetting]]));

	ChangeQuality();
}


FString LineTrace(FVector Start, FVector Direction, UWorld* World)
{
	FHitResult OutHit;
	const FVector End = Start + Direction * 2000.f;

	
	if (World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility)) if (OutHit.bBlockingHit) return OutHit.Component->GetName();
	return "";
}

void AManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PersonalDesk->UnHover();
	SettingsPanel->UnHoverLoadGame();
	SettingsPanel->UnHoverResetGame();
	SettingsPanel->UnHoverArrow(EWay::Center);
	TipsPanel->UnHoverChangeMenu();
	TipsPanel->UnHoverArrow(EWay::Center);
	const FString HitComponent = LineTrace(Camera->GetComponentLocation(), Camera->GetForwardVector(), GetWorld());
	if(HitComponent == "LeftBox") PersonalDesk->Hover(EWay::Sx);
	else if(HitComponent == "RightBox") PersonalDesk->Hover(EWay::Dx);
	else if(HitComponent == "CenterBox") PersonalDesk->Hover(EWay::Center);
	else if(HitComponent == "LoadGameBox") SettingsPanel->HoverLoadGame();
	else if(HitComponent == "ResetGameBox") SettingsPanel->HoverResetGame();
	else if(HitComponent == "LeftArrowBox") SettingsPanel->HoverArrow(EWay::Sx);
	else if(HitComponent == "RightArrowBox") SettingsPanel->HoverArrow(EWay::Dx);
	else if(HitComponent == "ToggleMenuBoxMenu") TipsPanel->HoverChangeMenu();
	else if(HitComponent == "LeftArrowBoxMenu") TipsPanel->HoverArrow(EWay::Sx);
	else if(HitComponent == "RightArrowBoxMenu") TipsPanel->HoverArrow(EWay::Dx);
}

void AManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &AManager::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AManager::Turn);
	
	PlayerInputComponent->BindAxis("LookUpMobile", this, &AManager::LookUpMobile);
	PlayerInputComponent->BindAxis("TurnMobile", this, &AManager::TurnMobile);

	
	PlayerInputComponent->BindAction("Touch", EInputEvent::IE_Pressed, this, &AManager::Touch);
}

void AManager::ChangeQuality() const
{
	GEngine->GetGameUserSettings()->SetOverallScalabilityLevel(GraphicSetting);
	GEngine->GetGameUserSettings()->SetResolutionScaleValueEx(40.f + (GraphicSetting) * 20);
	if(GraphicSetting >= 2) GEngine->GetGameUserSettings()->SetVSyncEnabled(true);
	else GEngine->GetGameUserSettings()->SetVSyncEnabled(false);
	GEngine->GetGameUserSettings()->ApplySettings(false);
}

void AManager::Touch()
{
	const FString HitComponent = LineTrace(Camera->GetComponentLocation(), Camera->GetForwardVector(), GetWorld());
	if(HitComponent == "LeftBox") PersonalDesk->Press(EWay::Sx);
	else if(HitComponent == "RightBox") PersonalDesk->Press(EWay::Dx);
	else if(HitComponent == "CenterBox")
	{
		if(PersonalDesk->GetGameStatus() == EGameProgess::ChoosingCountry)
		{
			SettingsPanel->SetLoadGameEnabled(false);
			SettingsPanel->SetResetGameEnable(true);
		}
		PersonalDesk->Press(EWay::Center);
	}
	else if(HitComponent == "DoorBox")
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit,true);
	}
	else if(HitComponent == "LoadGameBox")
	{
		PersonalDesk->LoadGame();
		SettingsPanel->SetLoadGameEnabled(false);
		SettingsPanel->SetResetGameEnable(true);
	}
	else if(HitComponent == "ResetGameBox") UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	else if(HitComponent == "RightArrowBox")
	{
		if(GraphicSetting == 3) GraphicSetting = 0;
		else GraphicSetting += 1;

		SettingsPanel->SetGraphicText(FText::FromString(GraphicQualityName[GraphicSettings[GraphicSetting]]));
		ChangeQuality();
	}
	else if(HitComponent == "LeftArrowBox")
	{
		if(GraphicSetting == 0) GraphicSetting = 3;
		else GraphicSetting -= 1;

		SettingsPanel->SetGraphicText(FText::FromString(GraphicQualityName[GraphicSettings[GraphicSetting]]));
		ChangeQuality();
	}
	else if(HitComponent == "ToggleMenuBoxMenu") TipsPanel->ToggleMenuType();
	else if(HitComponent == "RightArrowBoxMenu") TipsPanel->ClickArrow(EWay::Dx);
	else if(HitComponent == "LeftArrowBoxMenu") TipsPanel->ClickArrow(EWay::Sx);
	
}

void AManager::Turn(float Value) {
	FRotator CameraRotation = Camera->GetRelativeRotation();
	CameraRotation.Yaw += Value* GetWorld()->GetDeltaSeconds() * 60.f;
	Camera->SetRelativeRotation(CameraRotation);
}

void AManager::LookUp(float Value) {
	FRotator CameraRotation = Camera->GetRelativeRotation();
	CameraRotation.Pitch += Value * GetWorld()->GetDeltaSeconds() * 40.f;
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch, -80.f, 20.f);
	Camera->SetRelativeRotation(CameraRotation);
}

void AManager::TurnMobile(float Value) {
	FRotator CameraRotation = Camera->GetRelativeRotation();
	CameraRotation.Yaw += FMath::Sign(Value)*(Value * Value) * GetWorld()->GetDeltaSeconds() * 80.f;
	Camera->SetRelativeRotation(CameraRotation);
}

void AManager::LookUpMobile(float Value) {
	FRotator CameraRotation = Camera->GetRelativeRotation();
	CameraRotation.Pitch += FMath::Sign(Value)*Value * Value * GetWorld()->GetDeltaSeconds() * 60.f;
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch, -80.f, 20.f);
	Camera->SetRelativeRotation(CameraRotation);
}