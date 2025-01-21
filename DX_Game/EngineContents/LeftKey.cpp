#include "PreCompile.h"
#include "LeftKey.h"
#include <EnginePlatform/EngineInput.h>
#include "Player.h"


ALeftKey::ALeftKey()
{

}

ALeftKey::~ALeftKey()
{

}

void ALeftKey::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	FPlayerLogic& LogicValue = Player->GetPlayerLogic();
	if (UEngineInput::IsFree(VK_LEFT)) {
		if (PlayerLogic->bIsGround) {
			LogicValue.SetVelocityX(0.0f);
			SetActiveFalse();
			return;
		}
	}
	if (UEngineInput::IsPress(VK_LEFT)) {
		if (LogicValue.bIsMoveable) {
			if (LogicValue.bIsGround) {
				float VelocityX = UEngineMath::Lerp(0.0f, 260.0f, UEngineMath::Clamp(UEngineInput::GetPressTime(VK_LEFT) * 4.0f, 0.0f, 1.0f));
				LogicValue.SetVelocityX(-VelocityX);
			}
		}
		if (!(LogicValue.bIsUsingSkill) && LogicValue.bIsGround) {
			Player->ChangeAnimation("Walk");
		}
	}
}

void ALeftKey::SetActiveTrue()
{
	AActorFunction::SetActiveTrue();
	Player->SetActorRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void ALeftKey::SetActiveFalse()
{
	AActorFunction::SetActiveFalse();
}
