#include "PreCompile.h"
#include "Player.h"
#include "PlayerFuncManager.h"
#include "MyGameInstance.h"


void APlayer::SetHpPercentDamage(float _Percent)
{
	GetGameInstance<MyGameInstance>()->PlayerStatus.PrevHp = GetGameInstance<MyGameInstance>()->PlayerStatus.Hp;
	GetGameInstance<MyGameInstance>()->PlayerStatus.PrevHpPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.Hp / GetGameInstance<MyGameInstance>()->PlayerStatus.MaxHp;
	GetGameInstance<MyGameInstance>()->PlayerStatus.Hp -= GetGameInstance<MyGameInstance>()->PlayerStatus.MaxHp * _Percent;
	GetGameInstance<MyGameInstance>()->PlayerStatus.CurHpPercent = GetGameInstance<MyGameInstance>()->PlayerStatus.Hp / GetGameInstance<MyGameInstance>()->PlayerStatus.MaxHp;
	GetGameInstance<MyGameInstance>()->PlayerStatus.bIsHpChange = true;
	if (GetGameInstance<MyGameInstance>()->PlayerStatus.Hp <= 0)
	{
		GetGameInstance<MyGameInstance>()->PlayerStatus.Hp = 0;
	}
}

void APlayer::CheckKey(float _DeltaTime)
{
	if (UEngineInput::IsAllFree())
	{
		if (true == PlayerLogic.bIsGround)
		{
			ChangeAnimation("Stand");
		}
		else if (true == PlayerLogic.bIsJumping || true == PlayerLogic.bIsFalling)
		{
			ChangeAnimation("Jump");
		}
	}

	if (UEngineInput::IsDown(VK_LEFT)) {
		if (false ==DirFunctionMap["VK_LEFT"]->IsActive() ) {
			DirFunctionMap["VK_LEFT"]->SetActiveTrue();
		}

	}
	if (UEngineInput::IsDown(VK_RIGHT)) {
		if (false == DirFunctionMap["VK_RIGHT"]->IsActive()) {
			DirFunctionMap["VK_RIGHT"]->SetActiveTrue();
		}
		
	}
	if (UEngineInput::IsDown(VK_DOWN)) {
		if (false == DirFunctionMap["VK_DOWN"]->IsActive()) {
			DirFunctionMap["VK_DOWN"]->SetActiveTrue();
		}
	}
	if (UEngineInput::IsDown(VK_UP)) {
		if (false == DirFunctionMap["VK_UP"]->IsActive()) {
			DirFunctionMap["VK_UP"]->SetActiveTrue();
		}
	}


	if (UEngineInput::IsDown('C')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('C'))();
	}
	if (UEngineInput::IsDown('Z')) {
		PlayerFuncManager->GetFunc(PlayerFuncManager->GetFuncName('Z'))();
	}

}