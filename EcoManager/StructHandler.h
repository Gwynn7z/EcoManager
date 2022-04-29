#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StructHandler.generated.h"

UENUM(BlueprintType)
enum class EGameProgess : uint8
{
	ChoosingCountry,
	PendingToStart,
	GameStarted,
	GameFinished,
	GameLost
};

UENUM(BlueprintType)
enum class EGraphicSettings : uint8
{
	Low,
	Medium,
	High,
	Epic
};

static TMap<EGraphicSettings, FString> GraphicQualityName = {
	{EGraphicSettings::Low, "Bassa"},
	{EGraphicSettings::Medium, "Media"},
	{EGraphicSettings::High, "Alta"},
	{EGraphicSettings::Epic, "Epica"}
};

UENUM(BlueprintType)
enum class EWay : uint8
{
	Dx,
	Sx,
	Center
};

UENUM(BlueprintType)
enum class EArmMovement : uint8
{
	Close,
	Open,
	TurnRight,
	TurnLeft,
};

UENUM(BlueprintType)
enum class EShowingMenuType : uint8
{
	Rules,
	Suggestions
};

UENUM(BlueprintType)
enum class EStats : uint8
{
	Money,
	Like,
	Eco,
	Energy,
	Instruction,
	Safety,
	Research,
	GreenSpace
};

UENUM(BlueprintType)
enum class EPowerPlants : uint8
{
	Carbon,
	Gas,
	Nuclear,
	Sun,
	Wind,
	Water
};

UENUM(BlueprintType)
enum class EModulatorType : uint8
{
	DirectlyProportional,
	InverselyProportional
};

UENUM(BlueprintType)
enum class EPowerPlantAction : uint8
{
	AddPowerPlant,
	RemovePowerPlant
};

UENUM(BlueprintType)
enum class ETurnType : uint8
{
	QuestionTurn,
	ConsequenceTurn
};

USTRUCT(BlueprintType)
struct FCountryData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPowerPlants, int32>  PowerSources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStats, int32>  Statistics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tips;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* FlagImage;
};

USTRUCT(BlueprintType)
struct FActivators
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinMonth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPowerPlants> PowerPlantsNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStats, int32>  CountryStatisticsNeeded;
};


USTRUCT(BlueprintType)
struct FModulators
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EStats> InputStatistics;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPowerPlants> InputResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LowerPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HigherPercentage;
};

USTRUCT(BlueprintType)
struct FQuestions : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestionIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActivationTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RightTextChoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LeftTextChoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStats, FModulators> RightValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStats, FModulators> LeftValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPowerPlantAction, EPowerPlants> RightPowerPlantAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPowerPlantAction, EPowerPlants> LeftPowerPlantAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActivators Activators;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> RightConsequencesIndexes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> LeftConsequencesIndexes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EStats> Strengths;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPowerPlants> PowerPlantsTips;
};

USTRUCT(BlueprintType)
struct FPercentageHandler 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EStats> InputStatistics;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPowerPlants> InputResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LowerPercentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HigherPercentage;
};

USTRUCT(BlueprintType)
struct FConsequences : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ActivationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BasePercentage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPercentageHandler> PercentageHandler;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SuccessText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FailText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStats, int32> SuccessValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStats, int32> FailValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPowerPlantAction, EPowerPlants> RightPowerPlantAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPowerPlantAction, EPowerPlants> LeftPowerPlantAction;
};

USTRUCT(BlueprintType)
struct FRulesTextures : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* RuleTextures;
};

USTRUCT(BlueprintType)
struct FPowerPlantsTips : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPowerPlants PowerPlant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> Textures;
};

UCLASS()
class ECOMANAGER_API UStructHandler : public UObject
{
	GENERATED_BODY()
	
};
