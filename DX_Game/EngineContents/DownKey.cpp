#include "PreCompile.h"
#include "DownKey.h"
#include <EnginePlatform/EngineInput.h>
#include "Player.h"


ADownKey::ADownKey()
{

}

ADownKey::~ADownKey()
{

}

void ADownKey::Tick(float _DeltaTime)
{
	APlayerFunction::Tick(_DeltaTime);
	if (UEngineInput::IsFree(VK_DOWN)) {
		if (PlayerLogic->bIsGround) {
			// 콜리전 원래대로
			Player->StandCollision();
			SetActiveFalse();
			return;
		}
	}
	if (UEngineInput::IsPress(VK_DOWN)) {
		if (PlayerLogic->bIsUsingSkill)
		{
			return;
		}

	}
}

void ADownKey::SetActiveTrue()
{
	APlayerFunction::SetActiveTrue();
	if (!PlayerLogic->bIsProneable) 
	{
		SetActiveFalse();
		return;
	}
	if (PlayerLogic->bIsGround ) {
		Player->ProneCollision();
		Player->ChangeAnimation("Prone");
	}
}

void ADownKey::SetActiveFalse()
{
	APlayerFunction::SetActiveFalse();
}
