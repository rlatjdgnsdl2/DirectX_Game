#include "PreCompile.h"
#include "Player.h"

#include "PlayerFuncManager.h"
#include "JobComponent.h"
#include "Skill.h"

void APlayer::Start_Defying_Fate()
{
	SpriteRenderer->ChangeAnimation("UltimateDrive");
	PlayerFuncManager->GetFunc(EPlayer_Function::Defying_Fate)();
}

void APlayer::Update_Defying_Fate(float _DeltaTime)
{
	if (!JobComponent->GetSkill(EPlayer_Function::Defying_Fate)->IsActive())
	{
		FSM.ChangeState(EPlayer_State::Idle);
	}
}