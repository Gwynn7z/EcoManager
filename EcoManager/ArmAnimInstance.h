#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "StructHandler.h"
#include "ArmAnimInstance.generated.h"

class AArm;

UCLASS()
class ECOMANAGER_API UArmAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) void ChangeArmState(EArmMovement NewState);
	
	UFUNCTION() void SetOwner(AArm* NewArm);
	FORCEINLINE bool IsWaitingForAnswer() const { return bWaitingForAnswer; };
	
protected:
	UPROPERTY(BlueprintReadWrite) EArmMovement ArmMovement = EArmMovement::Close;
	UPROPERTY(BlueprintReadWrite) bool bWaitingForAnswer = false;
	
	UFUNCTION(BlueprintCallable) void Ready();
	UFUNCTION(BlueprintCallable) void RemovePanel();
	UFUNCTION(BlueprintCallable) void SetWaitingForAnswer();
	
private:
	UPROPERTY() AArm* Arm;
	
	
};
