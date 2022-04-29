#include "TimePanel.h"

// Sets default values
ATimePanel::ATimePanel()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/QuestionPanel/QuestionPanel.QuestionPanel'"));
	Mesh->SetStaticMesh(StaticMesh.Object);
	Mesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));

	TimeWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TimeWidget"));
	TimeWidgetComponent->SetupAttachment(RootComponent);
	TimeWidgetComponent->SetRelativeLocation(FVector(1.f, 0.f, 0.f));
	TimeWidgetComponent->SetRelativeScale3D(FVector(1.f, 0.5f, 0.5f));
	TimeWidgetComponent->SetDrawSize(FVector2D(800.f, 500.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> TimeWidgetAsset(TEXT("/Game/Widgets/TimeWidget"));
	const TSubclassOf<UUserWidget> TimeWidgetAssetClass = TimeWidgetAsset.Class;
	TimeWidgetComponent->SetWidgetClass(TimeWidgetAssetClass);
}

void ATimePanel::BeginPlay()
{
	Super::BeginPlay();
	TimeWidget = Cast<UTimePanelWidget>(TimeWidgetComponent->GetWidget());
}

void ATimePanel::SetTime(FText Text) const
{
	TimeWidget->SetTime(Text);
}

void ATimePanel::SetColor(FColor Color) const
{
	TimeWidget->SetTextColor(Color);
}

void ATimePanel::SetText(FText NewText, FColor NewColor) const
{
	TimeWidget->SetText(NewText, NewColor);
}
