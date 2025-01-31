#include "PreCompile.h"
#include "Player.h"
#include "JobComponent.h"
#include "PlayerFunction.h"
#include "PhysicsComponent.h"



void APlayer::Start_Move_Left()
{
	SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	SpriteRenderer->ChangeAnimation("Walk");
}

void APlayer::Update_Move_Left(float _DeltaTime)
{
	if (UEngineInput::IsDown(VK_RIGHT))
	{
		FSM.ChangeState(EPlayer_State::Move_Right);
		return;
	}
	if (UEngineInput::IsFree(VK_LEFT))
	{
		FSM.ChangeState(EPlayer_State::Idle);
		return;
	}
	if (UEngineInput::IsPress(VK_LEFT))
	{
		float VelocityX = UContentsPysics::ApplyWalk(UEngineInput::GetPressTime(VK_LEFT)*4.0f);
	
		PysicsComponent->SetVelocityX(-VelocityX);
	}

}

void APlayer::Start_Move_Right() 
{
	SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
	SpriteRenderer->ChangeAnimation("Walk");
}
void APlayer::Update_Move_Right(float _DeltaTime) 
{
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
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		float VelocityX = UContentsPysics::ApplyWalk(UEngineInput::GetPressTime(VK_RIGHT) * 4.0f);
		PysicsComponent->SetVelocityX(VelocityX);
	}
}


