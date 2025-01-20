#include "PreCompile.h"
#include "PlayerFuncManager.h"

#include <EngineCore/Actor.h>

#include "Player.h"
#include "Skill.h"
#include "Job.h"

UPlayerFuncManager::UPlayerFuncManager()
{
	std::shared_ptr<AActor> SharedPlayer(GetWorld()->GetMainPawn());
	Player = std::static_pointer_cast<APlayer>(SharedPlayer);

	{
		UEngineDelegate NewFunc;
		NewFunc += ([this]()
			{
				APlayer* Player = this->Player.lock().get();
				ASkill* Skill = Player->GetPlayerJob()->GetSkill("SwiftPhantom");
				if (nullptr != Skill) {
					if (Skill->IsActive()) {
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
				APlayer* Player = this->Player.lock().get();
				ASkill* Skill = Player->GetPlayerJob()->GetSkill("UltimateDrive");
				if (nullptr != Skill) {
					if (Skill->IsActive()) {
						Skill->SetActiveTrue();
					}
				}
			});
		SetFunc("UltimateDrive", NewFunc);
		SetFuncName('Z', "UltimateDrive");
	}
}


UPlayerFuncManager::~UPlayerFuncManager()
{

}
