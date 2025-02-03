#include "PreCompile.h"
#include "PlayerFuncManager.h"

#include <EngineCore/Actor.h>

#include "Player.h"
#include "Skill.h"
#include "JobComponent.h"

UPlayerFuncManager::UPlayerFuncManager()
{
	
}


UPlayerFuncManager::~UPlayerFuncManager()
{

}

void UPlayerFuncManager::BeginPlay()
{
	UActorComponent::BeginPlay();
	Player = dynamic_cast<APlayer*>(GetWorld()->GetMainPawn());
	{
		UEngineDelegate NewFunc;
		NewFunc += ([this]()
			{
				ASkill* Skill = Player->GetJobComponent()->GetSkill(EPlayer_Function::Swift_Phantom);
				if (nullptr != Skill) {
					if (false == Skill->IsActive()) {
						Skill->SetActiveTrue();
					}
				}
			});
		SetFunc('C',EPlayer_Function::Swift_Phantom, NewFunc);
	}

	{
		UEngineDelegate NewFunc;
		NewFunc += ([this]()
			{
				ASkill* Skill = Player->GetJobComponent()->GetSkill(EPlayer_Function::Ultimate_Drive);
				if (nullptr != Skill) {
					if (false==Skill->IsActive()) {
						Skill->SetActiveTrue();
					}
				}
			});
		SetFunc('Z', EPlayer_Function::Ultimate_Drive, NewFunc);
	}

	{
		UEngineDelegate NewFunc;
		NewFunc += ([this]()
			{
				ASkill* Skill = Player->GetJobComponent()->GetSkill(EPlayer_Function::Rift_Break);
				if (nullptr != Skill) {
					if (false == Skill->IsActive()) {
						Skill->SetActiveTrue();
					}
				}
			});
		SetFunc('W', EPlayer_Function::Rift_Break, NewFunc);
	}

	{
		UEngineDelegate NewFunc;
		NewFunc += ([this]()
			{
				ASkill* Skill = Player->GetJobComponent()->GetSkill(EPlayer_Function::Defying_Fate);
				if (nullptr != Skill) {
					if (false == Skill->IsActive()) {
						Skill->SetActiveTrue();
					}
				}
			});
		SetFunc('R', EPlayer_Function::Defying_Fate, NewFunc);
	}
}
