// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Grux_Stampede.h"
#include "../../Grux_AIController.h"
#include "../../Grux_AICharacter.h"
#include "../../Grux_AIAnimInst.h"
#include "../../../AIState.h"

UBTTask_Grux_Stampede::UBTTask_Grux_Stampede()
{
	NodeName = TEXT("Grux_Stampede");

	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Grux_Stampede::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	AAIController* Controller = OwnerComp.GetAIOwner();
	AGrux_AICharacter* GruxCharacter = Cast<AGrux_AICharacter>(Controller->GetPawn());

	if (IsValid(GruxCharacter)) {
		// Idle ������ ������ ������ �����ϰ� ����.
		AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

		if (IsValid(Target)) {
			GruxCharacter->Skill2_Stampede_Ready();

			return EBTNodeResult::Succeeded;
		}


		// Target�� ���� ��� �ൿ�� �����ϰ� Idle ���·� �ǵ���
		Controller->StopMovement();

		Cast<UGrux_AIAnimInst>(GruxCharacter->GetMesh()->GetAnimInstance())->ChangeAnim(EAIAnimType::Idle);
	}

	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_Grux_Stampede::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::AbortTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type();
}

void UBTTask_Grux_Stampede::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_Grux_Stampede::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
