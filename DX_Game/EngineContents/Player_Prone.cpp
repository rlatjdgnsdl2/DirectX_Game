#include "PreCompile.h"
#include "Player.h"


void APlayer::Start_Prone()
{
	SpriteRenderer->ChangeAnimation("Prone");
	ProneCollision();
}


void APlayer::Update_Prone(float _DeltaTime)
{
	if (UEngineInput::IsUp(VK_DOWN))
	{
		StandCollision();
		FSM.ChangeState(EPlayer_State::Idle);
		return;
	}
}