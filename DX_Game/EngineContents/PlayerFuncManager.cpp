#include "PreCompile.h"
#include "PlayerFuncManager.h"

#include <EngineCore/Actor.h>

#include "Player.h"
#include "Skill.h"
#include "Job.h"

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
				ASkill* Skill = Player->GetPlayerJob()->GetSkill("SwiftPhantom");
				if (nullptr != Skill) {
					if (false == Skill->IsActive()) {
						Skill->SetActiveTrue();
					}
				}
			});
		SetFunc("SwiftPhantom", NewFunc);
		SetFuncName('C', "SwiftPhantom");
	}

	{
		UEngineDelegate NewFunc;
		NewFunc += ([this]()
			{
				ASkill* Skill = Player->GetPlayerJob()->GetSkill("UltimateDrive");
				if (nullptr != Skill) {
					if (false==Skill->IsActive()) {
						Skill->SetActiveTrue();
					}
				}
			});
		SetFunc("UltimateDrive", NewFunc);
		SetFuncName('Z', "UltimateDrive");
	}
}
