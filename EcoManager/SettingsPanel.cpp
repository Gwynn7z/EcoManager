#include "SettingsPanel.h"

#include "Misc/OutputDeviceNull.h"

ASettingsPanel::ASettingsPanel()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/QuestionPanel/QuestionPanel.QuestionPanel'"));
	Mesh->SetStaticMesh(StaticMesh.Object);
	Mesh->SetRelativeScale3D(FVector(1.f, 2.f, 2.f));

	LeftArrowBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArrowBox"));
	LeftArrowBox->SetupAttachment(RootComponent);
	LeftArrowBox->SetRelativeLocation(FVector(0.f, 120.f, 60.f));
	LeftArrowBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	RightArrowBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightArrowBox"));
	RightArrowBox->SetupAttachment(RootComponent);
	RightArrowBox->SetRelativeLocation(FVector(0.f, -120.f, 60.f));
	RightArrowBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	LoadGameBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LoadGameBox"));
	LoadGameBox->SetupAttachment(RootComponent);
	LoadGameBox->SetRelativeScale3D(FVector(1.f, 3.75f, 0.75f));
	LoadGameBox->SetRelativeLocation(FVector(0.f, 0.f, -25.f));
	LoadGameBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	ResetGameBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ResetGameBox"));
	ResetGameBox->SetupAttachment(RootComponent);
	ResetGameBox->SetRelativeScale3D(FVector(1.f, 3.75f, 0.75f));
	ResetGameBox->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
	ResetGameBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	SettingsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextWidget"));
	SettingsWidgetComponent->SetupAttachment(RootComponent);
	SettingsWidgetComponent->SetRelativeLocation(FVector(1.f, 0.f, 0.f));
	SettingsWidgetComponent->SetRelativeScale3D(FVector(1.f, 0.5f, 0.5f));
	SettingsWidgetComponent->SetDrawSize(FVector2D(800.f, 500.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> SettingsPanelWidgetAsset(TEXT("/Game/Widgets/SettingsPanel"));
	const TSubclassOf<UUserWidget> SettingsPanelWidgetAssetClass = SettingsPanelWidgetAsset.Class;
	SettingsWidgetComponent->SetWidgetClass(SettingsPanelWidgetAssetClass);
}

void ASettingsPanel::BeginPlay()
{
	Super::BeginPlay();
	SettingsWidget = Cast<USettingsPanelWidget>(SettingsWidgetComponent->GetWidget());
}

void ASettingsPanel::SetGraphicText(FText Text) const
{
	SettingsWidget->SetGraphicText(Text);
}

void ASettingsPanel::HoverLoadGame() const
{
	SettingsWidget->HoverLoadGame();
}
void ASettingsPanel::UnHoverLoadGame() const
{
	SettingsWidget->UnHoverLoadGame();
}
void ASettingsPanel::HoverResetGame() const
{
	SettingsWidget->HoverResetGame();
}
void ASettingsPanel::UnHoverResetGame() const
{
	SettingsWidget->UnHoverResetGame();
}

void ASettingsPanel::SetResetGameEnable(bool bEnabled) const
{
	if(bEnabled) ResetGameBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	else ResetGameBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	SettingsWidget->SetResetGameEnable(bEnabled);
	
}
void ASettingsPanel::SetLoadGameEnabled(bool bEnabled) const
{
	if(bEnabled) LoadGameBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	else LoadGameBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	SettingsWidget->SetLoadGameEnabled(bEnabled);
}

void ASettingsPanel::HoverArrow(EWay ArrowWay) const
{
	FOutputDeviceNull Out;
	if(ArrowWay == EWay::Dx) SettingsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("HoverRight"), Out, nullptr, true);
	else if(ArrowWay == EWay::Sx) SettingsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("HoverLeft"), Out, nullptr, true);
	else
	{
		HoverArrow(EWay::Dx);
		HoverArrow(EWay::Sx);
	}
}	
void ASettingsPanel::UnHoverArrow(EWay ArrowWay) const
{
	FOutputDeviceNull Out;
	if(ArrowWay == EWay::Dx) SettingsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("UnHoverRight"), Out, nullptr, true);
	else if(ArrowWay == EWay::Sx) SettingsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("UnHoverLeft"), Out, nullptr, true);
	else
	{
		UnHoverArrow(EWay::Dx);
		UnHoverArrow(EWay::Sx);
	}
}