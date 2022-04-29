#include "Desk.h"
#include "EcoManagerSave.h"
#include "Arm.h"
#include "Components/WidgetComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "Animation/AnimInstance.h"
#include "Bars.h"
#include "Timer.h"
#include "LeftScreen.h"
#include "RightScreen.h"
#include "StructHandler.h"
#include "Manager.h"
#include "TimePanel.h"
#include "Kismet/GameplayStatics.h"

ADesk::ADesk()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMesh(TEXT("SkeletalMesh'/Game/Desk/Desk.Desk'"));
	Mesh->SetSkeletalMesh(SkelMesh.Object);

	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftBox"));
	LeftTrigger->SetupAttachment(RootComponent);
	LeftTrigger->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	LeftTrigger->SetRelativeLocation(FVector(-185.f,170.f,135.f));
	LeftTrigger->SetRelativeRotation(FRotator(35.f, 0.f, 0.f));
	LeftTrigger->SetRelativeScale3D(FVector(1.25f, 2.75f, 2.f));

	CenterTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CenterBox"));
	CenterTrigger->SetupAttachment(RootComponent);
	CenterTrigger->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	CenterTrigger->SetRelativeLocation(FVector(-185.f,0.f,130.f));
	CenterTrigger->SetRelativeRotation(FRotator(30.f, 0.f, 0.f));
	CenterTrigger->SetRelativeScale3D(FVector(1.25f, 1.5f, 2.f));

	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RightBox"));
	RightTrigger->SetupAttachment(RootComponent);
	RightTrigger->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	RightTrigger->SetRelativeLocation(FVector(-185.f,-170.f,135.f));
	RightTrigger->SetRelativeRotation(FRotator(35.f, 0.f, 0.f));
	RightTrigger->SetRelativeScale3D(FVector(1.25f, 2.75f, 2.f));

	RightArrow = CreateDefaultSubobject<UWidgetComponent>(TEXT("RightArrow"));
	RightArrow->SetupAttachment(Mesh, FName("RightButtonSocket"));

	LeftArrow = CreateDefaultSubobject<UWidgetComponent>(TEXT("LeftArrow"));
	LeftArrow->SetupAttachment(Mesh, FName("LeftButtonSocket"));
	
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/Widgets/ArrowWidget"));
	const TSubclassOf<UUserWidget> ArrowAssetClass = WidgetClass.Class;
	RightArrow->SetWidgetClass(ArrowAssetClass);
	LeftArrow->SetWidgetClass(ArrowAssetClass);

	CenterWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CenterWidget"));
	CenterWidget->SetupAttachment(Mesh, FName("CenterSocket"));
	static ConstructorHelpers::FClassFinder<UUserWidget> CenterWidgetClass(TEXT("/Game/Widgets/CenterWidget"));
	const TSubclassOf<UUserWidget> CenterWidgetAssetClass = CenterWidgetClass.Class;
	CenterWidget->SetWidgetClass(CenterWidgetAssetClass);

	BarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BarWidget"));
	BarWidget->SetupAttachment(RootComponent);
	BarWidget->SetRelativeLocation(FVector(4.f, 0.f, 102.f));
	BarWidget->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	BarWidget->SetRelativeScale3D(FVector(1.f, 0.19f, 0.18f));
	BarWidget->SetDrawSize(FVector2D(500.f, 1760.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> BarWidgetClass(TEXT("/Game/Widgets/BarWidget"));
	const TSubclassOf<UUserWidget> BarWidgetAssetClass = BarWidgetClass.Class;
	BarWidget->SetWidgetClass(BarWidgetAssetClass);

	LeftScreen = CreateDefaultSubobject<UWidgetComponent>(TEXT("LeftScreen"));
	LeftScreen->SetupAttachment(RootComponent);
	LeftScreen->SetRelativeLocation(FVector(60.f, 140.f, 102.f));
	LeftScreen->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	LeftScreen->SetRelativeScale3D(FVector(1.f, 0.5f, 0.5f));
	LeftScreen->SetDrawSize(FVector2D(500.f, 1000.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> LeftScreenWidgetClass(TEXT("/Game/Widgets/LeftScreen"));
	const TSubclassOf<UUserWidget> LeftScreenWidgetAssetClass = LeftScreenWidgetClass.Class;
	LeftScreen->SetWidgetClass(LeftScreenWidgetAssetClass);

	RightScreen = CreateDefaultSubobject<UWidgetComponent>(TEXT("RightScreen"));
	RightScreen->SetupAttachment(RootComponent);
	RightScreen->SetRelativeLocation(FVector(25.f, -143.f, 102.f));
	RightScreen->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	RightScreen->SetRelativeScale3D(FVector(1.f, 0.4f, 0.4f));
	RightScreen->SetDrawSize(FVector2D(500.f, 1000.f));
	static ConstructorHelpers::FClassFinder<UUserWidget> RightScreenWidgetClass(TEXT("/Game/Widgets/RightScreen"));
	const TSubclassOf<UUserWidget> RightScreenWidgetAssetClass = RightScreenWidgetClass.Class;
	RightScreen->SetWidgetClass(RightScreenWidgetAssetClass);
	
	static ConstructorHelpers::FObjectFinder<UClass> AnimBlueprint(TEXT("AnimBlueprint'/Game/Desk/DeskAnimBP.DeskAnimBP_C'"));
	if (AnimBlueprint.Object != nullptr) Mesh->SetAnimInstanceClass(AnimBlueprint.Object);
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RightClickAsset(TEXT("AnimMontage'/Game/Desk/RightClickMontage.RightClickMontage'"));
	RightClick = RightClickAsset.Object;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> LeftClickAsset(TEXT("AnimMontage'/Game/Desk/LeftClickMontage.LeftClickMontage'"));
	LeftClick = LeftClickAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> CountryDataAsset(TEXT("DataTable'/Game/Structs/CountryData.CountryData'"));
	CountryData = CountryDataAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> QuestionsDataAsset(TEXT("DataTable'/Game/Structs/Questions.Questions'"));
	QuestionsData = QuestionsDataAsset.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> ConsequencesDataAsset(TEXT("DataTable'/Game/Structs/Consequences.Consequences'"));
	ConsequencesData = ConsequencesDataAsset.Object;
}

void ADesk::BeginPlay()
{
	Super::BeginPlay();
	TimerWidget = Cast<UTimer>(CenterWidget->GetWidget());
	LeftScreenWidget = Cast<ULeftScreen>(LeftScreen->GetWidget());
	RightScreenWidget = Cast<URightScreen>(RightScreen->GetWidget());
	BarsWidget = Cast<UBars>(BarWidget->GetWidget());
	DeskOwner = Cast<AManager>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(AActor* TempArm = UGameplayStatics::GetActorOfClass(GetWorld(), AArm::StaticClass())) Arm = Cast<AArm>(TempArm);
	Arm->CreateChannel(this);

	if(AActor* TempTimePanel = UGameplayStatics::GetActorOfClass(GetWorld(), ATimePanel::StaticClass())) TimePanel = Cast<ATimePanel>(TempTimePanel);
	if(AActor* TipsPanelTemp = UGameplayStatics::GetActorOfClass(GetWorld(), ATipsPanel::StaticClass())) TipsPanel = Cast<ATipsPanel>(TipsPanelTemp);

	CurrentMonthTimer = MaxMonthTimer;

	TArray<FCountryData*> TempData;
	CountryData->GetAllRows<FCountryData>("", TempData);
	for(auto Item : TempData)
	{
		FCountryData* NewData = new FCountryData;
		NewData->Name = Item->Name;
		NewData->Statistics = Item->Statistics;
		NewData->FlagImage = Item->FlagImage;
		NewData->PowerSources = Item->PowerSources;
		NewData->Tips = Item->Tips;
		TotalData.Add(NewData);
	}

	DataShowingIndex = 0;
	GameProgess = EGameProgess::ChoosingCountry;
	UpdateCountryData(TotalData[DataShowingIndex]);

	TurnType = ETurnType::QuestionTurn;
	QuestionsData->GetAllRows<FQuestions>("", TotalQuestions);
	ConsequencesData->GetAllRows<FConsequences>("", TotalConsequences);

	TArray<EPowerPlants> PowerPlants = {EPowerPlants::Carbon, EPowerPlants::Nuclear, EPowerPlants::Gas, EPowerPlants::Sun, EPowerPlants::Water, EPowerPlants::Wind};
	for(EPowerPlants PowerPlant : PowerPlants) BuiltPowerPlants.Add(PowerPlant, 0);
}

void ADesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADesk::Hover(EWay ArrowSide) const
{
	FOutputDeviceNull Out;
	if(ArrowSide == EWay::Dx) RightArrow->GetWidget()->CallFunctionByNameWithArguments(TEXT("Hover"), Out, nullptr, true);
	else if(ArrowSide == EWay::Sx) LeftArrow->GetWidget()->CallFunctionByNameWithArguments(TEXT("Hover"), Out, nullptr, true);
	else TimerWidget->SetHover(true);
}

void ADesk::UnHover() const
{
	FOutputDeviceNull Out;
	RightArrow->GetWidget()->CallFunctionByNameWithArguments(TEXT("UnHover"), Out, nullptr, true);
	LeftArrow->GetWidget()->CallFunctionByNameWithArguments(TEXT("UnHover"), Out, nullptr, true);
	TimerWidget->SetHover(false);
}

void ADesk::Press(EWay PressedButton)
{
	if(TurnType == ETurnType::ConsequenceTurn) return;
	
	if(PressedButton == EWay::Center)
	{
		if(GameProgess == EGameProgess::ChoosingCountry)
		{
			TimerWidget->SetText(FText::FromString("VAI"));
			ChosenCountryData = TotalData[DataShowingIndex];
			InitialGreenSpace = ChosenCountryData->Statistics[EStats::GreenSpace];
			GameProgess = EGameProgess::PendingToStart;
			UpdateQuestionsPool();
		}
		else if(GameProgess == EGameProgess::PendingToStart)
		{
			SaveGame();
			DeltaQuestions = 0;
			TimerWidget->SetText(FText::FromString("-"));
			GetWorld()->GetTimerManager().SetTimer(MonthTimer, this, &ADesk::MonthDown, 1.f, true);
			GameProgess = EGameProgess::GameStarted;
			SendQuestion();
		}
	}
	else
	{
		if(GameProgess == EGameProgess::ChoosingCountry)
		{
			if(PressedButton == EWay::Sx) DataShowingIndex -= 1;
			else if(PressedButton == EWay::Dx) DataShowingIndex += 1;
			
			if(DataShowingIndex < 0) DataShowingIndex = TotalData.Num() -1;
			else if(DataShowingIndex >= TotalData.Num()) DataShowingIndex = 0;
			
			UpdateCountryData(TotalData[DataShowingIndex]);
		}
		else if(Arm->IsWaitingForAnswer())
		{
			if(PressedButton == EWay::Sx)
			{
				Arm->ChangeArmState(EArmMovement::TurnLeft);
				if(Mesh->GetAnimInstance()) Mesh->GetAnimInstance()->Montage_Play(LeftClick);
				
			}
			else
			{
				Arm->ChangeArmState(EArmMovement::TurnRight);
				if(Mesh->GetAnimInstance())Mesh->GetAnimInstance()->Montage_Play(RightClick);
			}
			DeltaQuestions += 1;
			LastChoice = PressedButton;
		}
	}
}

//Start Run
void ADesk::ReceiveQuestion()
{
	if(TurnType == ETurnType::ConsequenceTurn) GetWorld()->GetTimerManager().SetTimer(ThinkTimer, this, &ADesk::RemoveConsequence, 5.f, false);
	else if(CurrentQuestion) TipsPanel->SetCurrentSuggestions(CurrentQuestion->PowerPlantsTips);
}

void ADesk::RemoveConsequence() const
{

	if(LastChoice == EWay::Dx) Arm->ChangeArmState(EArmMovement::TurnRight);
	else if(LastChoice == EWay::Sx) Arm->ChangeArmState(EArmMovement::TurnLeft);
}

void ADesk::MonthDown()
{
	CurrentMonthTimer -= 1;
	if(CurrentMonthTimer <= 0) UpdateMonth();
}

void ADesk::UpdateMonth()
{
	CurrentMonthTimer = MaxMonthTimer;
	Month += 1;
	TimePanel->SetTime(FText::FromString(FString::FromInt(Month)));
	
	ChosenCountryData->Statistics[EStats::Money] += ChosenCountryData->Statistics[EStats::Like] * 0.2;
	if(ChosenCountryData->Statistics[EStats::GreenSpace] < (InitialGreenSpace - 10))
	{
		const int32 Value = ((InitialGreenSpace - 10) - ChosenCountryData->Statistics[EStats::GreenSpace]) / 2;
		ChosenCountryData->Statistics[EStats::Eco] -= Value;
		ChosenCountryData->Statistics[EStats::Like] -= Value;
	}
	else if(ChosenCountryData->Statistics[EStats::GreenSpace] > (InitialGreenSpace + 10))
	{
		const int32 Value = (ChosenCountryData->Statistics[EStats::GreenSpace] - (InitialGreenSpace + 10)) / 2;
		ChosenCountryData->Statistics[EStats::Eco] += Value;
		ChosenCountryData->Statistics[EStats::Like] += Value;
	}

	if(DeltaQuestions == 0) ChosenCountryData->Statistics[EStats::Like] -= 16;
	else if(DeltaQuestions < 2) ChosenCountryData->Statistics[EStats::Like] -= 8;
	else if(DeltaQuestions < 4) ChosenCountryData->Statistics[EStats::Like] -= 5;
	else if(DeltaQuestions < 8) ChosenCountryData->Statistics[EStats::Like] += 5;
	else if(DeltaQuestions >= 10) ChosenCountryData->Statistics[EStats::Like] += 8;
	else if(DeltaQuestions >= 15) ChosenCountryData->Statistics[EStats::Like] += 16;
	DeltaQuestions = 0;
	
	SaveGame(true);

	if(Month >= 100)
	{
		TimePanel->SetText(FText::FromString("Fine mandato"), FColor::Green);
		TimePanel->SetColor(FColor::Green);
		TipsPanel->SetInfosPanel();
		GameProgess = EGameProgess::GameFinished;
		GetWorld()->GetTimerManager().ClearTimer(MonthTimer);
		DeleteSave();
	}
}

//Start Movement
void ADesk::NotifyReady()
{
	GetWorld()->GetTimerManager().SetTimer(ThinkTimer, this, &ADesk::SendQuestion, 5.f, false);
}

void ADesk::SendQuestion()
{
	if(GameProgess == EGameProgess::GameLost || GameProgess == EGameProgess::GameFinished) return;
	
	if(TurnType == ETurnType::ConsequenceTurn)
	{
		ChooseConsequenceResult();
		if(LastChoice == EWay::Dx) Arm->SendConsequence(FText::FromString(CurrentConsequence->SuccessText));
		else if(LastChoice == EWay::Sx) Arm->SendConsequence(FText::FromString(CurrentConsequence->FailText));
	}
	else Arm->SendQuestion(FText::FromString(CurrentQuestion->QuestionText), FText::FromString(CurrentQuestion->LeftTextChoice), FText::FromString(CurrentQuestion->RightTextChoice));
}

void ADesk::UpdateCountryData(FCountryData* CurrentData)
{
	if(CurrentData == nullptr)
	{
		CurrentData = ChosenCountryData;
		for(const auto& Stats : ChosenCountryData->Statistics)
		{
			if(Stats.Key == EStats::Instruction || Stats.Key == EStats::Research || Stats.Key == EStats::Safety) continue;
			if(Stats.Value <= 0)
			{
				TimePanel->SetText(FText::FromString("Hai perso"), FColor::Red);
				TimePanel->SetColor(FColor::Red);
				TipsPanel->SetInfosPanel();
				GameProgess = EGameProgess::GameLost;
				GetWorld()->GetTimerManager().ClearTimer(MonthTimer);
				DeleteSave();
			}
		}
	}
	
	LeftScreenWidget->SetCountry(FText::FromString(CurrentData->Name));

	FString Infos = "";
	for(FString Strings : CurrentData->Tips) Infos += Strings + "\n\n";
	LeftScreenWidget->SetInfos(FText::FromString(Infos));

	BarsWidget->SetBarValue(CurrentData->Statistics);
	BarsWidget->SetBarValue(CurrentData->Statistics);
	BarsWidget->SetBarValue(CurrentData->Statistics);
	BarsWidget->SetBarValue(CurrentData->Statistics);

	RightScreenWidget->SetBarValue(CurrentData->Statistics);
	RightScreenWidget->SetFlagImage(CurrentData->FlagImage);
}

void ADesk::UpdateQuestionsPool()
{
	if(GameProgess == EGameProgess::GameLost || GameProgess == EGameProgess::GameFinished) return;
	
	TArray<FQuestions*> AvailableQuestions;
	for(auto &Question : TotalQuestions)
	{
		if(Question->Activators.MinMonth > Month) continue;

		bool bHasPowerPlant = true;
		for(const EPowerPlants PowerPlant : Question->Activators.PowerPlantsNeeded)
		{
			if(BuiltPowerPlants[PowerPlant] == 0)
			{
				bHasPowerPlant = false;
				break;
			}
		}
		if(!bHasPowerPlant) continue;

		bool bHasStats = true;
		for(const auto StatNeeded : Question->Activators.CountryStatisticsNeeded)
		{
			if(StatNeeded.Value < ChosenCountryData->Statistics[StatNeeded.Key])
			{
				bHasStats = false;
				break;
			}
		}
		if(!bHasStats) continue;
		if(AnsweredQuestions.Contains(Question)) continue;
		AvailableQuestions.Add(Question);
	}
	for(int32 i=0; i<5; i++)
	{
		if(AvailableQuestions.Num() == 0) break;
		const int32 Index = FMath::RandRange(0, AvailableQuestions.Num()-1);
		FQuestions* NewQuestion = AvailableQuestions[Index];
		
		QuestionsPool.Add(NewQuestion);
		AvailableQuestions.Remove(NewQuestion);
	}

	bool bHelpUsed = false;
	for(auto &CountryStat : ChosenCountryData->Statistics)
	{
		if(CountryStat.Value < 15)
		{
			for(auto& Question : AvailableQuestions)
			{
				if(Question->Strengths.Contains(CountryStat.Key))
				{
					QuestionsPool.Add(Question);
					bHelpUsed = true;
					break;
				}
			}
		}
		if(bHelpUsed) break;
	}

	if(QuestionsPool.Num() == 0)
	{
		AnsweredQuestions.Empty();
		UpdateQuestionsPool();
		return;
	}
	const int32 Index = FMath::RandRange(0, QuestionsPool.Num()-1);
	CurrentQuestion = QuestionsPool[Index];
}


void ADesk::WorkOnQuestionsResults(TMap<EStats, FModulators> Stats, const TArray<int32> Consequences, TMap<EPowerPlantAction, EPowerPlants> PowerPlantsActions)
{
	for(auto &Stat : Stats)
	{
		int32 Value = Stat.Value.MaxValue;
		if(Stat.Value.InputResources.Num() != 0 || Stat.Value.InputStatistics.Num() != 0)
		{
			int32 ComparingPercentage = 0;
			for(const EPowerPlants InputResource : Stat.Value.InputResources) ComparingPercentage = ChosenCountryData->PowerSources[InputResource];
			for(const EStats InputStat : Stat.Value.InputStatistics) ComparingPercentage = ChosenCountryData->Statistics[InputStat];

			const int32 NewValue = ((ComparingPercentage / Stat.Value.HigherPercentage) - (Stat.Value.LowerPercentage / Stat.Value.HigherPercentage)) * 100;
			Value = NewValue * (Stat.Value.MaxValue - Stat.Value.MinValue) / 100 + Stat.Value.MinValue;
				
		}
		ChosenCountryData->Statistics[Stat.Key] += Value;
	}

	for(const auto PowerPlantAction : PowerPlantsActions)
	{
		for(auto& PowerPlant : BuiltPowerPlants)
		{
			if(PowerPlantAction.Value == PowerPlant.Key)
			{
				if(PowerPlantAction.Key == EPowerPlantAction::AddPowerPlant) PowerPlant.Value += 1;
				else PowerPlant.Value -= 1;
				if(PowerPlant.Value < 0) PowerPlant.Value = 0;
			}
		}
	}

	if(Consequences.Num() > 0)
	{
		const int32 Index = FMath::RandRange(0, Consequences.Num()-1);

		for(const auto& Consequence : TotalConsequences)
		{
			if(Consequence->Index == Consequences[Index])
			{
				ConsequencesPool.Add(Consequence);
				break;
			}
		}
	}
}

void ADesk::ChooseConsequenceResult()
{
	int32 Percentage = CurrentConsequence->BasePercentage;
	for(auto &Handler : CurrentConsequence->PercentageHandler)
	{
		int32 ComparingPercentage = 0;
		for(const EPowerPlants InputResource :Handler.InputResources) ComparingPercentage = ChosenCountryData->PowerSources[InputResource];
		for(const EStats InputStat : Handler.InputStatistics) ComparingPercentage = ChosenCountryData->Statistics[InputStat];
		Percentage += ComparingPercentage * (Handler.HigherPercentage  -Handler.LowerPercentage) / 100 + Handler.LowerPercentage;
	}

	const int32 RandomChoice = FMath::RandRange(0, 100);
	if(Percentage >= RandomChoice) LastChoice = EWay::Dx;
	else LastChoice = EWay::Sx;
}

void ADesk::WorkOnConsequencesResults(TMap<EStats, int32> Stats, TMap<EPowerPlantAction, EPowerPlants> PowerPlantsActions)
{
	for(auto &Stat : Stats) ChosenCountryData->Statistics[Stat.Key] += Stat.Value;
	
	for(const auto PowerPlantAction : PowerPlantsActions)
	{
		for(auto& PowerPlant : BuiltPowerPlants)
		{
			if(PowerPlantAction.Value == PowerPlant.Key)
			{
				if(PowerPlantAction.Key == EPowerPlantAction::AddPowerPlant) PowerPlant.Value += 1;
				else PowerPlant.Value -= 1;
				if(PowerPlant.Value < 0) PowerPlant.Value = 0;
			}
		}
	}
}

void ADesk::UpdateCurrentQuestionsStatistics()
{
	if(GameProgess == EGameProgess::GameLost || GameProgess == EGameProgess::GameFinished) return;
	
	if(TurnType == ETurnType::ConsequenceTurn)
	{
		if(LastChoice == EWay::Sx) WorkOnConsequencesResults(CurrentConsequence->FailValues, CurrentConsequence->LeftPowerPlantAction);
		else WorkOnConsequencesResults(CurrentConsequence->SuccessValues, CurrentConsequence->RightPowerPlantAction);
		ConsequencesPool.Remove(CurrentConsequence);
		CurrentConsequence = nullptr;
		TurnType = ETurnType::QuestionTurn;
		UpdateCountryData();
		return;
	}
	
	if(LastChoice == EWay::Sx)	WorkOnQuestionsResults( CurrentQuestion->LeftValues, CurrentQuestion->LeftConsequencesIndexes, CurrentQuestion->LeftPowerPlantAction);
	else WorkOnQuestionsResults( CurrentQuestion->RightValues, CurrentQuestion->RightConsequencesIndexes, CurrentQuestion->RightPowerPlantAction);

	QuestionsPool.Remove(CurrentQuestion);
	AnsweredQuestions.Add(CurrentQuestion);
	
	if(QuestionsPool.Num() == 0) UpdateQuestionsPool();
	else
	{
		const int32 Index = FMath::RandRange(0, QuestionsPool.Num()-1);
		CurrentQuestion = QuestionsPool[Index];
	}
	
	if(FMath::RandRange(0, 100) < 40 && ConsequencesPool.Num() > 0)
	{
		CurrentConsequence = ConsequencesPool[0];
		TurnType = ETurnType::ConsequenceTurn;
	}
	else TurnType = ETurnType::QuestionTurn;
	
	for(auto &Stats : ChosenCountryData->Statistics)
	{
		if(Stats.Value < 0) Stats.Value = 0;
		else if(Stats.Value > 100) Stats.Value = 100;
	}
	
	UpdateCountryData();
	SaveGame();
}

void ADesk::SaveGame(bool bJustMonth)
{
	if(bJustMonth)
	{
		UEcoManagerSave* SaveGame = Cast<UEcoManagerSave>(UGameplayStatics::LoadGameFromSlot(TEXT("DefaultSlot"),0));
		SaveGame->Month = Month;
		SaveGame->MonthTimer = CurrentMonthTimer;
		SaveGame->Stats = ChosenCountryData->Statistics;
		UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("DefaultSlot"), 0);
		return;
	}
	UEcoManagerSave* SaveGame = Cast<UEcoManagerSave>(UGameplayStatics::CreateSaveGameObject(UEcoManagerSave::StaticClass()));
	SaveGame->Month = Month;
	SaveGame->MonthTimer = CurrentMonthTimer;
	
	SaveGame->Stats = ChosenCountryData->Statistics;
	SaveGame->CountryName = ChosenCountryData->Name;
	
	for(const auto& Question : AnsweredQuestions) SaveGame->QuestionsPool.Add(Question->QuestionIndex);
	for(const auto& Question : QuestionsPool) SaveGame->QuestionsPool.Add(Question->QuestionIndex);
	for(const auto& Consequence : ConsequencesPool) SaveGame->ConsequencesPool.Add(Consequence->Index);
	
	SaveGame->InitialGreenSpace = InitialGreenSpace;
	SaveGame->TurnType = TurnType;
	UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("DefaultSlot"), 0);
}

void ADesk::LoadGame()
{
	UEcoManagerSave* SaveGame = Cast<UEcoManagerSave>(UGameplayStatics::LoadGameFromSlot(TEXT("DefaultSlot"),0));
	if(SaveGame)
	{
		Month = SaveGame->Month;
		CurrentMonthTimer = SaveGame->MonthTimer;
		
		TimePanel->SetTime(FText::FromString(FString::FromInt(Month)));
		
		for(const auto& Country : TotalData)
		{
			if(Country->Name.Equals(SaveGame->CountryName))
			{
				FCountryData* NewData = new FCountryData;
				NewData->Name = Country->Name;
				NewData->Statistics = SaveGame->Stats;
				NewData->FlagImage = Country->FlagImage;
				NewData->PowerSources = Country->PowerSources;
				NewData->Tips = Country->Tips;
				ChosenCountryData = NewData;
				break;
			}
		}
		
		for(auto& Question : TotalQuestions)
		{
			if(SaveGame->AnsweredQuestions.Contains(Question->QuestionIndex)) AnsweredQuestions.Add(Question);
			if(SaveGame->QuestionsPool.Contains(Question->QuestionIndex)) QuestionsPool.Add(Question);
		}
		for(auto& Consequence : ConsequencesPool) if(SaveGame->ConsequencesPool.Contains(Consequence->Index)) ConsequencesPool.Add(Consequence);


		InitialGreenSpace = SaveGame->InitialGreenSpace;

		TimerWidget->SetText(FText::FromString("VAI"));
		GameProgess = EGameProgess::PendingToStart;

		TurnType = SaveGame->TurnType;
		if(TurnType == ETurnType::ConsequenceTurn) CurrentConsequence = ConsequencesPool[0];
		else
		{
			if(QuestionsPool.Num() == 0)
			{
				AnsweredQuestions.Empty();
				UpdateQuestionsPool();
			}
			else
			{
				const int32 Index = FMath::RandRange(0, QuestionsPool.Num()-1);
				CurrentQuestion = QuestionsPool[Index];
			}
		}
		UpdateCountryData();
	}
}

void ADesk::DeleteSave()
{
	UGameplayStatics::DeleteGameInSlot(TEXT("DefaultSlot"),0);
}

EGameProgess ADesk::GetGameStatus() const
{
	return GameProgess;
}

