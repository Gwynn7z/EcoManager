#include "Arm.h"
#include "Animation/AnimInstance.h"
#include "ArmAnimInstance.h"
#include "Desk.h"
#include "QuestionPanel.h"
#include "Kismet/GameplayStatics.h"

AArm::AArm()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkelMesh"));
	SetRootComponent(Mesh);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> SkelMeshAsset(TEXT("SkeletalMesh'/Game/Arm/Arm.Arm'"));
	Mesh->SetSkeletalMesh(SkelMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UClass> AnimBlueprint(TEXT("AnimBlueprint'/Game/Arm/ArmAnimBP.ArmAnimBP_C'"));
	if (AnimBlueprint.Object != nullptr)
	{
		Mesh->SetAnimInstanceClass(AnimBlueprint.Object);
	}

}

void AArm::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UArmAnimInstance>(Mesh->GetAnimInstance());
	AnimInstance->SetOwner(this);
}

void AArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Own
void AArm::CreateChannel(ADesk* Desk)
{
	BoundDesk = Desk;
}

void AArm::Start()
{
	SpawnPanel();
	ChangeArmState(EArmMovement::Open);
}

void AArm::SendQuestion(FText Text, FText LeftChoice, FText RightChoice)
{
	Start();
	QuestionPanel->SendQuestion(Text, LeftChoice, RightChoice);
}

void AArm::SendConsequence(FText Text)
{
	Start();
	QuestionPanel->SendConsequence(Text);
}

void AArm::SpawnPanel()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.bNoFail = true;
	QuestionPanel = GetWorld()->SpawnActor<AQuestionPanel>(Mesh->GetSocketLocation(FName("QuestionPanelSocket")), FRotator::ZeroRotator, SpawnParams);
	QuestionPanel->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("QuestionPanelSocket"));
}

//Bridge Functions
bool AArm::IsWaitingForAnswer() const
{
	return AnimInstance->IsWaitingForAnswer();
}

void AArm::ChangeArmState(EArmMovement NewMovement) const
{
	AnimInstance->ChangeArmState(NewMovement);
}

//Instance Called
void AArm::RemovePanel() const
{
	QuestionPanel->Destroy();
	BoundDesk->UpdateCurrentQuestionsStatistics();
}

void AArm::NotifyWaiting() const
{
	if(BoundDesk) BoundDesk->ReceiveQuestion();
}

void AArm::BeginCycle() const
{
	if(BoundDesk) BoundDesk->NotifyReady();
}
