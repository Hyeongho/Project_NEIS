// Fill out your copyright notice in the Description page of Project Settings.



#include "BT_Service_AIBossMonsterAlive.h"
#include "../../AI_BossMonster.h"
#include "../../../Animation/BHG_AIBossAnimInstance.h"
#include "../../../../AI/AIState.h"
#include "../../../Component/AbilityComponent.h"
#include "../../../Ability/DefaultAbility.h"
#include "../../../../AI/AICharacter.h"

UBT_Service_AIBossMonsterAlive::UBT_Service_AIBossMonsterAlive()
	: Super()
{
	NodeName = TEXT("BossMonsterAlive");

	Interval = 0.5f;
	RandomDeviation = 0.1f;

	InitTime = 2.f;
}

void UBT_Service_AIBossMonsterAlive::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	if (IsValid(Controller))
	{
		AAI_BossMonster* AIBossMonster = Cast<AAI_BossMonster>(Controller->GetPawn());

		if (IsValid(AIBossMonster))
		{
			UBHG_AIBossAnimInstance* AIAnim = Cast<UBHG_AIBossAnimInstance>(AIBossMonster->GetMesh()->GetAnimInstance());

			if (AIBossMonster->GetRespawnOn() && !AIBossMonster->GetBossDie())
			{
				Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Owner"), AIBossMonster);

				int32 HpValue = Cast<AAICharacter>(AIBossMonster)->GetAIState()->GetHP(); 

				Controller->GetBlackboardComponent()->SetValueAsInt(TEXT("BossHP"), HpValue);

				// 만약 어빌리티가 종료됬음에도 컨트롤러의 AbilityEnable이 True라면 false로 바꿔준다. 
				bool AbilityEnable = Controller->GetBlackboardComponent()->GetValueAsBool(TEXT("AbilityEnable"));

				if (AIBossMonster->GetBossAbilityEnable() && AbilityEnable)
				{
					Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("AbilityEnable"), false);
				}


				


				//Ability CoolTime Update

				UAbilityComponent* BossAbillyComp = AIBossMonster->GetComponentByClass<UAbilityComponent>();
				

				//Default Attack2 

				float AbilityCoolTime = 0.f;
				
				AbilityCoolTime = BossAbillyComp->FindAbility(TEXT("AIBossDefaultAttack2"))->GetAbilityCoolTime();

				if (AbilityCoolTime > 0.f)
					Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("DefaultAttack2Enable"), false);

				else
					Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("DefaultAttack2Enable"), true);

				//Skill1

				AbilityCoolTime = BossAbillyComp->FindAbility(TEXT("AIBossSkill1"))->GetAbilityCoolTime();

				if (AbilityCoolTime > 0.f)
					Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("Skill1Enable"), false);

				else
					Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("Skill1Enable"), true);
				
				//Skill2

				AbilityCoolTime = BossAbillyComp->FindAbility(TEXT("AIBossSkill2"))->GetAbilityCoolTime();

				if (AbilityCoolTime > 0.f)
					Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("Skill2Enable"), false);

				else
					Controller->GetBlackboardComponent()->SetValueAsBool(TEXT("Skill2Enable"), true);


			}
			
		}

		else
		{
			Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Owner"), nullptr);
		}
	}
}
