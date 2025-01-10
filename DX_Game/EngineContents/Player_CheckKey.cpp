#include "PreCompile.h"
#include "Player.h"
#include "PlayerFuncManager.h"



void APlayer::CheckKey(float _DeltaTime)
{
	if (UEngineInput::IsAllFree()) {
		if (BoolValue.IsGroundValue) {
			ChangeAnimation(PAnimation_State::Stand);
		}
		else if (BoolValue.IsJumpingValue || BoolValue.IsFallingValue) {
			ChangeAnimation(PAnimation_State::Jump);
		}
	}

	if (UEngineInput::IsPress(VK_LEFT) || UEngineInput::IsDown(VK_LEFT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_LEFT))();
		
	}
	if (UEngineInput::IsPress(VK_RIGHT) || UEngineInput::IsDown(VK_RIGHT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_RIGHT))();
	}
	if (UEngineInput::IsPress(VK_DOWN) || UEngineInput::IsDown(VK_DOWN)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_DOWN))();
	}
	if (UEngineInput::IsUp(VK_DOWN)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_DOWN)).Up();
	}
	if (UEngineInput::IsPress('C') || UEngineInput::IsDown('C')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('C'))();
	}
	if (UEngineInput::IsPress('Z') || UEngineInput::IsDown('Z')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('Z'))();
	}

}