#include "PreCompile.h"
#include "Player.h"
#include "PlayerFuncManager.h"



void APlayer::CheckKey(float _DeltaTime)
{
	if (UEngineInput::IsAllFree()) 
	{
		if (true == PlayerLogic.bIsGround) 
		{
			ChangeAnimation(PAnimation_State::Stand);
		}
		else if (true == PlayerLogic.bIsJumping || true == PlayerLogic.bIsFalling) 
		{
			ChangeAnimation(PAnimation_State::Jump);
		}
	}

	if (UEngineInput::IsDown(VK_LEFT)) {
		DirFunctionMap["VK_LEFT"].lock()->SetActiveTrue();
	}
	if (UEngineInput::IsDown(VK_RIGHT)) {
		DirFunctionMap["VK_RIGHT"].lock()->SetActiveTrue();
	}
	if (UEngineInput::IsDown(VK_DOWN)) {
		DirFunctionMap["VK_DOWN"].lock()->SetActiveTrue();
	}
	if (UEngineInput::IsDown(VK_UP)) {
		DirFunctionMap["VK_UP"].lock()->SetActiveTrue();
	}
	if (UEngineInput::IsDown('C')) {
		PlayerFuncManager.lock()->GetFunc(PlayerFuncManager.lock()->GetFuncName('C'))();
	}
	if (UEngineInput::IsDown('Z')) {
		PlayerFuncManager.lock()->GetFunc(PlayerFuncManager.lock()->GetFuncName('Z'))();
	}

}