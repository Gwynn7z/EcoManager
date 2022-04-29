
#include "ArmAnimInstance.h"
#include "Arm.h"

void UArmAnimInstance::ChangeArmState(EArmMovement NewState)
{
	ArmMovement = NewState;
}

void UArmAnimInstance::SetOwner(AArm* NewArm)
{
	Arm = NewArm;
}

void UArmAnimInstance::SetWaitingForAnswer()
{
	bWaitingForAnswer = true;
	Arm->NotifyWaiting();
}

void UArmAnimInstance::Ready()
{
	Arm->BeginCycle();
}

void UArmAnimInstance::RemovePanel()
{
	Arm->RemovePanel();
}
