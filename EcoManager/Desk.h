#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "StructHandler.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Desk.generated.h"

class UWidgetComponent;
class UTimer;
class ULeftScreen;
class URightScreen;
class AArm;
class UBars;
class AManager;
class ACarrier;
class UDataTable;
class ATimePanel;
class ATipsPanel;

UCLASS()
class ECOMANAGER_API ADesk : public AActor
{
	GENERATED_BODY()
	
public:	
	ADesk();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere) UBoxComponent* LeftTrigger;
	UPROPERTY(EditAnywhere) UBoxComponent* CenterTrigger;
	UPROPERTY(EditAnywhere) UBoxComponent* RightTrigger;

	UPROPERTY(EditAnywhere) UWidgetComponent* RightArrow;
	UPROPERTY(EditAnywhere) UWidgetComponent* LeftArrow;
	UPROPERTY(EditAnywhere) UWidgetComponent* CenterWidget;
	UPROPERTY(EditAnywhere) UWidgetComponent* BarWidget;
	UPROPERTY(EditAnywhere) UWidgetComponent* LeftScreen;
	UPROPERTY(EditAnywhere) UWidgetComponent* RightScreen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* CountryData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* QuestionsData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataTable* ConsequencesData;
	
	UFUNCTION() void UnHover() const;
	UFUNCTION() void Hover(EWay ArrowSide) const;

	UFUNCTION() void NotifyReady();
	
	UFUNCTION() void Press(EWay PressedButton);
	UFUNCTION() void ReceiveQuestion();

	UFUNCTION() void UpdateCurrentQuestionsStatistics();

	UFUNCTION() void LoadGame();
	UFUNCTION() EGameProgess GetGameStatus() const;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY() UTimer* TimerWidget;
	UPROPERTY() URightScreen* RightScreenWidget;
	UPROPERTY() ULeftScreen* LeftScreenWidget;
	UPROPERTY() UBars* BarsWidget;

private:
	UFUNCTION() void SaveGame(bool bJustMonth = false);
	UFUNCTION()
	static void DeleteSave();
		
	int32 Month = 0;
	EWay LastChoice = EWay::Center;

	UFUNCTION() void WorkOnQuestionsResults(TMap<EStats, FModulators> Stats, const TArray<int32> Consequences, TMap<EPowerPlantAction, EPowerPlants> PowerPlantsActions);
	UFUNCTION() void WorkOnConsequencesResults(TMap<EStats, int32> Stats, TMap<EPowerPlantAction, EPowerPlants> PowerPlantsActions);
	UFUNCTION() void ChooseConsequenceResult();
	UFUNCTION() void UpdateQuestionsPool();
	UFUNCTION() void RemoveConsequence() const;
	UFUNCTION() void UpdateMonth();
	UFUNCTION() void MonthDown();
	UFUNCTION() void SendQuestion();
	
	UPROPERTY() AManager* DeskOwner;
	UPROPERTY() AArm* Arm;
	UPROPERTY() ATimePanel* TimePanel;
	UPROPERTY() ATipsPanel* TipsPanel;
	
	int32 DataShowingIndex;
	TArray<FCountryData*> TotalData;
	FCountryData* ChosenCountryData;
	void UpdateCountryData(FCountryData* CurrentData = nullptr);

	TArray<FQuestions*> TotalQuestions;
	TArray<FConsequences*> TotalConsequences; 
	
	TArray<FQuestions*> QuestionsPool;
	TArray<FQuestions*> AnsweredQuestions;
	TArray<FConsequences*> ConsequencesPool;
	ETurnType TurnType;
	
	FQuestions* CurrentQuestion;
	FConsequences* CurrentConsequence;
	
	TMap<EPowerPlants, int32> BuiltPowerPlants;
	int32 InitialGreenSpace;
	
	EGameProgess GameProgess;

	FTimerHandle MonthTimer;
	FTimerHandle ThinkTimer;

	int32 DeltaQuestions;
	int32 CurrentMonthTimer;
	const int32 MaxMonthTimer = 60.f;

	UPROPERTY() UAnimMontage* RightClick;
	UPROPERTY() UAnimMontage* LeftClick;
};
