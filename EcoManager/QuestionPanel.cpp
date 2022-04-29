
#include "QuestionPanel.h"

AQuestionPanel::AQuestionPanel()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/QuestionPanel/QuestionPanel.QuestionPanel'"));
	Mesh->SetStaticMesh(StaticMesh.Object);

	TextWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextWidget"));
	TextWidgetComponent->SetupAttachment(RootComponent);
	TextWidgetComponent->SetRelativeLocation(FVector(1.f, 0.f, 0.f));
	TextWidgetComponent->SetRelativeScale3D(FVector(1.f, 0.5f, 0.5f));
	TextWidgetComponent->SetDrawSize(FVector2D(800.f, 500.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> QuestionPanelWidgetAsset(TEXT("/Game/Widgets/QuestionPanel"));
	const TSubclassOf<UUserWidget> QuestionPanelWidgetAssetClass = QuestionPanelWidgetAsset.Class;
	TextWidgetComponent->SetWidgetClass(QuestionPanelWidgetAssetClass);
}

void AQuestionPanel::BeginPlay()
{
	Super::BeginPlay();
	TextWidget = Cast<UQuestionPanelWidget>(TextWidgetComponent->GetWidget());
}

void AQuestionPanel::SendQuestion(FText Text, FText LeftChoice, FText RightChoice) const
{
	TextWidget->SendQuestion(Text, LeftChoice, RightChoice);
}

void AQuestionPanel::SendConsequence(FText Text) const
{
	TextWidget->SendConsequence(Text);
}