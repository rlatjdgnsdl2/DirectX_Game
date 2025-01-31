#include "PreCompile.h"
#include "Player.h"

#include "JobComponent.h"
#include "PlayerFunction.h"
#include "PlayerFuncManager.h"
#include "PhysicsComponent.h"
#include "Skill.h"


void APlayer::Start_Idle()
{
	SpriteRenderer->ChangeAnimation("Stand");
	PysicsComponent->SetVelocity(FVector::ZERO);
}

void APlayer::Update_Idle(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		FSM.ChangeState(EPlayer_State::Move_Left);
		return;
	}
	if (UEngineInput::IsPress(VK_RIGHT)) {

		FSM.ChangeState(EPlayer_State::Move_Right);
		return;
	}
	if (UEngineInput::IsDown(VK_DOWN)) {

		FSM.ChangeState(EPlayer_State::Prone);
		return;

	}


	{
		int Key = PlayerFuncManager->GetKey(EPlayer_Function::Ultimate_Drive);
		if (Key == -1)
		{
			return;
		}
		if (UEngineInput::IsPress(Key))
		{
			FSM.ChangeState(EPlayer_State::Ultimate_Drive);
			return;
		}
	}

	{
		int Key = PlayerFuncManager->GetKey(EPlayer_Function::Swift_Phantom);
		if (Key == -1)
		{
			return;
		}
		if (UEngineInput::IsPress(Key))
		{
			FSM.ChangeState(EPlayer_State::Swift_Phantom);
			return;
		}
	}
}
