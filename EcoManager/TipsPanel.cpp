
#include "TipsPanel.h"

#include "Misc/OutputDeviceNull.h"

ATipsPanel::ATipsPanel()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/QuestionPanel/QuestionPanel.QuestionPanel'"));
	Mesh->SetStaticMesh(StaticMesh.Object);
	Mesh->SetRelativeScale3D(FVector(1.f, 2.f, 2.f));

	LeftArrowBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArrowBoxMenu"));
	LeftArrowBox->SetupAttachment(RootComponent);
	LeftArrowBox->SetRelativeLocation(FVector(0.f, 180.f, 0.f));
	LeftArrowBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	RightArrowBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightArrowBoxMenu"));
	RightArrowBox->SetupAttachment(RootComponent);
	RightArrowBox->SetRelativeLocation(FVector(0.f, -180.f, 0.f));
	RightArrowBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	ToggleMenuBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ToggleMenuBoxMenu"));
	ToggleMenuBox->SetupAttachment(RootComponent);
	ToggleMenuBox->SetRelativeScale3D(FVector(1.f, 3.75f, 0.75f));
	ToggleMenuBox->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	ToggleMenuBox->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);

	TipsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextWidget"));
	TipsWidgetComponent->SetupAttachment(RootComponent);
	TipsWidgetComponent->SetRelativeLocation(FVector(1.f, 0.f, 0.f));
	TipsWidgetComponent->SetRelativeScale3D(FVector(1.f, 0.5f, 0.5f));
	TipsWidgetComponent->SetDrawSize(FVector2D(800.f, 500.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> TipsPanelWidgetAsset(TEXT("/Game/Widgets/TipsWidget"));
	const TSubclassOf<UUserWidget> TipsPanelWidgetAssetClass = TipsPanelWidgetAsset.Class;
	TipsWidgetComponent->SetWidgetClass(TipsPanelWidgetAssetClass);

	static ConstructorHelpers::FObjectFinder<UDataTable> RulesDataAsset(TEXT("DataTable'/Game/Structs/RulesTextures.RulesTextures'"));
	RulesData = RulesDataAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PowerPlantsTipsDataAsset(TEXT("DataTable'/Game/Structs/PowerPlantsTips.PowerPlantsTips'"));
	PowerPlantsTipsData = PowerPlantsTipsDataAsset.Object;
	
	CurrentMenu = EShowingMenuType::Rules;

	static ConstructorHelpers::FObjectFinder<UTexture2D> LegendaAsset(TEXT("Texture2D'/Game/Images/Tips/Infos.Infos'"));

	if (LegendaAsset.Object != NULL)
	{
		Legenda = LegendaAsset.Object;
	}
}

void ATipsPanel::BeginPlay()
{
	Super::BeginPlay();
	TipsWidget = Cast<UTipsPanelWidget>(TipsWidgetComponent->GetWidget());
	
	RulesData->GetAllRows<FRulesTextures>("", RulesTexturesDB);
	for(const auto& Rule : RulesTexturesDB) RulesTextures.Add(Rule->RuleTextures);
	
	PowerPlantsTipsData->GetAllRows<FPowerPlantsTips>("", PowerPlantsTipsDB);

	SuggestionTextures = {{EPowerPlants::Carbon, TArray<UTexture2D*>()}, {EPowerPlants::Nuclear, TArray<UTexture2D*>()}, {EPowerPlants::Gas, TArray<UTexture2D*>()}, {EPowerPlants::Sun, TArray<UTexture2D*>()}, {EPowerPlants::Water, TArray<UTexture2D*>()}, {EPowerPlants::Wind, TArray<UTexture2D*>()}};
	for(const auto& PowerPlantTip : PowerPlantsTipsDB) SuggestionTextures[PowerPlantTip->PowerPlant] =  PowerPlantTip->Textures;
}

void ATipsPanel::SetCurrentSuggestions(TArray<EPowerPlants> Suggestions)
{
	CurrentSuggestions.Empty();
	CurrentSuggestionsIndex = 0;
	CurrentSuggestions.Add(Legenda);
	for(const EPowerPlants PowerPlant : Suggestions) CurrentSuggestions.Append(SuggestionTextures[PowerPlant]);
	if(CurrentMenu == EShowingMenuType::Suggestions) ToggleMenuType();
}

void ATipsPanel::ToggleMenuType()
{
	
	if(CurrentMenu == EShowingMenuType::Rules && CurrentSuggestions.Num() > 0)
	{
		CurrentMenu = EShowingMenuType::Suggestions;
		TipsWidget->SetChangeMenu(FText::FromString("Informazioni"));
		TipsWidget->SetCurrentImage(CurrentSuggestions[CurrentSuggestionsIndex]);
	}
	else
	{
		CurrentMenu = EShowingMenuType::Rules;
		TipsWidget->SetChangeMenu(FText::FromString("Regole"));
		TipsWidget->SetCurrentImage(RulesTextures[CurrentRulesIndex]);
	}
	
}

void ATipsPanel::ClickArrow(EWay Way)
{
	if(Way == EWay::Dx)
	{
		if(CurrentMenu == EShowingMenuType::Rules) CurrentRulesIndex +=1;
		else CurrentSuggestionsIndex +=1;
	}
	else if(Way == EWay::Sx)
	{
		if(CurrentMenu == EShowingMenuType::Rules) CurrentRulesIndex -= 1;
		else CurrentSuggestionsIndex -= 1;
	}
	if(CurrentSuggestionsIndex >= CurrentSuggestions.Num()) CurrentSuggestionsIndex = 0;
	else if(CurrentSuggestionsIndex < 0) CurrentSuggestionsIndex = CurrentSuggestions.Num() -1;
	
	if(CurrentRulesIndex >= RulesTextures.Num()) CurrentRulesIndex = 0;
	else if(CurrentRulesIndex < 0) CurrentRulesIndex = RulesTextures.Num() -1;

	if(CurrentMenu == EShowingMenuType::Rules) TipsWidget->SetCurrentImage(RulesTextures[CurrentRulesIndex]);
	else TipsWidget->SetCurrentImage(CurrentSuggestions[CurrentSuggestionsIndex]);
}

void ATipsPanel::HoverArrow(EWay ArrowWay) const
{
	FOutputDeviceNull Out;
	if(ArrowWay == EWay::Dx) TipsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("HoverRight"), Out, nullptr, true);
	else if(ArrowWay == EWay::Sx) TipsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("HoverLeft"), Out, nullptr, true);
	else
	{
		HoverArrow(EWay::Dx);
		HoverArrow(EWay::Sx);
	}
}	
void ATipsPanel::UnHoverArrow(EWay ArrowWay) const
{
	FOutputDeviceNull Out;
	if(ArrowWay == EWay::Dx) TipsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("UnHoverRight"), Out, nullptr, true);
	else if(ArrowWay == EWay::Sx) TipsWidgetComponent->GetWidget()->CallFunctionByNameWithArguments(TEXT("UnHoverLeft"), Out, nullptr, true);
	else
	{
		UnHoverArrow(EWay::Dx);
		UnHoverArrow(EWay::Sx);
	}
}

void ATipsPanel::HoverChangeMenu() const
{
	TipsWidget->HoverChangeMenu();
}
void ATipsPanel::UnHoverChangeMenu() const
{
	TipsWidget->UnHoverChangeMenu();
}

void ATipsPanel::SetInfosPanel()
{
	CurrentMenu = EShowingMenuType::Rules;
	CurrentRulesIndex = RulesTextures.Num() - 1;
	TipsWidget->SetCurrentImage(RulesTextures[CurrentRulesIndex]);
}