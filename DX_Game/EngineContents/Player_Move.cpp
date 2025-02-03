#include "PreCompile.h"
#include "Player.h"

#include "PlayerFuncManager.h"
#include "PhysicsComponent.h"



void APlayer::Start_Move_Left()
{
	SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	SpriteRenderer->ChangeAnimation("Walk");
}

void APlayer::Update_Move_Left(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		float VelocityX = UContentsPysics::ApplyWalk(UEngineInput::GetPressTime(VK_LEFT) * 4.0f);
		PysicsComponent->SetVelocityX(-VelocityX);
	}
	if (UEngineInput::IsDown(VK_RIGHT))
	{
		FSM.ChangeState(EPlayer_State::Move_Right);
		return;
	}
	if (UEngineInput::IsDown(VK_DOWN))
	{
		FSM.ChangeState(EPlayer_State::Prone);
		return;
	}

	if (UEngineInput::IsFree(VK_LEFT))
	{
		FSM.ChangeState(EPlayer_State::Idle);
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

void APlayer::Start_Move_Right() 
{
	SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	SpriteRenderer->ChangeAnimation("Walk");
}
void APlayer::Update_Move_Right(float _DeltaTime) 
{
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		float VelocityX = UContentsPysics::ApplyWalk(UEngineInput::GetPressTime(VK_RIGHT) * 4.0f);
		PysicsComponent->SetVelocityX(VelocityX);
	}
	if (UEngineInput::IsDown(VK_LEFT))
	{
		FSM.ChangeState(EPlayer_State::Move_Left);
		return;
	}
	if (UEngineInput::IsFree(VK_RIGHT))
	{
		FSM.ChangeState(EPlayer_State::Idle);
		return;
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

	
}


