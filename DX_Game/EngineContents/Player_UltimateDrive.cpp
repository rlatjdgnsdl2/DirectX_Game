#include "PreCompile.h"
#include "Player.h"

#include "PlayerFuncManager.h"
#include "PhysicsComponent.h"


void APlayer::Start_Ultimate_Drive()
{
	SpriteRenderer->ChangeAnimation("UltimateDrive");
	PlayerFuncManager->GetFunc(EPlayer_Function::Ultimate_Drive)();
}

void APlayer::Update_Ultimate_Drive(float _DeltaTime)
{
	if (UEngineInput::IsPress(VK_LEFT))
	{
		float VelocityX = UContentsPysics::ApplyWalk(UEngineInput::GetPressTime(VK_LEFT) * 4.0f);
		SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
		PysicsComponent->SetVelocityX(-VelocityX);
	}
	if (UEngineInput::IsUp(VK_LEFT)|| UEngineInput::IsUp(VK_RIGHT))
	{
		PysicsComponent->SetVelocityX(0.0f);
	}
	if (UEngineInput::IsPress(VK_RIGHT))
	{
		float VelocityX = UContentsPysics::ApplyWalk(UEngineInput::GetPressTime(VK_RIGHT) * 4.0f);
		SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
		PysicsComponent->SetVelocityX(VelocityX);
	}

	if (UEngineInput::IsUp(PlayerFuncManager->GetKey(EPlayer_Function::Ultimate_Drive)))
	{
		FSM.ChangeState(EPlayer_State::Idle);
		return;
	}
	
}
