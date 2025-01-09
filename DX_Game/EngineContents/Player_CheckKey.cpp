#include "PreCompile.h"
#include "Player.h"
#include "PlayerFuncManager.h"



void APlayer::CheckKey(float _DeltaTime)
{

	if (UEngineInput::IsPress('C')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('C')).Press();
	}
	if (UEngineInput::IsPress(VK_LEFT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_LEFT)).Press();
	}
	
	if (UEngineInput::IsPress(VK_RIGHT)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_RIGHT)).Press();
	}
	if (UEngineInput::IsPress(VK_DOWN)) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName(VK_DOWN)).Press();
	}
	if (UEngineInput::IsPress('Z')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('Z')).Press();
	}

}