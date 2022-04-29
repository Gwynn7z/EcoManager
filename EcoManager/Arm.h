#pragma once

#include "CoreMinimal.h"

#include "ArmAnimInstance.h"
#include "GameFramework/Actor.h"
#include "StructHandler.h"
#include "Arm.generated.h"

class AQuestionPanel;
class ADesk;

UCLASS()
class ECOMANAGER_API AArm : public AActor
{
	GENERATED_BODY()
	
public:	
	AArm();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animazioni") UArmAnimInstance* AnimInstance;

	//Bridge Functions	
	UFUNCTION() bool IsWaitingForAnswer() const;
	UFUNCTION() void ChangeArmState(EArmMovement NewMovement) const;

	//Instance Called
	UFUNCTION() void BeginCycle() const;
	UFUNCTION() void NotifyWaiting() const;
	UFUNCTION() void RemovePanel() const;

	//Own
	UFUNCTION() void SpawnPanel();
	UFUNCTION() void CreateChannel(ADesk* Desk);
	UFUNCTION() void SendQuestion(FText Text, FText LeftChoice, FText RightChoice);
	UFUNCTION() void SendConsequence(FText Text);
	
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY() AQuestionPanel* QuestionPanel;
	UPROPERTY() ADesk* BoundDesk;

	UFUNCTION() void Start();
};
