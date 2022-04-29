#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "StructHandler.h"
#include "EcoManagerSave.generated.h"

UCLASS()
class ECOMANAGER_API UEcoManagerSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 Month;

	UPROPERTY()
	int32 MonthTimer;
	
	
	UPROPERTY()
	int32 InitialGreenSpace;

	UPROPERTY()
	TMap<EStats, int32> Stats;

	UPROPERTY()
	FString CountryName;

	UPROPERTY()
	TArray<int32> QuestionsPool;

	UPROPERTY()
	TArray<int32> AnsweredQuestions;

	UPROPERTY()
	TArray<int32> ConsequencesPool;

	UPROPERTY()
	ETurnType TurnType;
	
};
