#include "PreCompile.h"
#include "Player.h"
#include "PlayerFuncManager.h"



void APlayer::CheckKey(float _DeltaTime)
{
	if (UEngineInput::IsAllFree()){
		ChangeAnimation(PAnimation_State::Stand);
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
	if (UEngineInput::IsPress('C')|| UEngineInput::IsDown('C')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('C'))();
	}
	if (UEngineInput::IsPress('Z') || UEngineInput::IsDown('Z')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('Z'))();
	}

}