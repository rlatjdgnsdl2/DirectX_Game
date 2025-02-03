#include "PreCompile.h"
#include "Player.h"

#include "PlayerFuncManager.h"

#include "Job_Phantom.h"
#include "JobComponent.h"
#include "Skill.h"


void APlayer::Start_Rift_Break() 
{
	SpriteRenderer->ChangeAnimation("UltimateDrive");
	PlayerFuncManager->GetFunc(EPlayer_Function::Rift_Break)();
}
void APlayer::Update_Rift_Break(float _DeltaTime) 
{
	if (!JobComponent->GetSkill(EPlayer_Function::Rift_Break)->IsActive())
	{
		FSM.ChangeState(EPlayer_State::Idle);
	}
}
