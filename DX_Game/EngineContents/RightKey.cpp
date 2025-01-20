#include "PreCompile.h"
#include "RightKey.h"
#include "Player.h"


ARightKey::ARightKey()
{

}

ARightKey::~ARightKey()
{

}




void ARightKey::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	FPlayerLogic& LogicValue = Player->GetPlayerLogic();
	if (UEngineInput::IsFree(VK_RIGHT)) {
		if (PlayerLogic->bIsGround) {
			LogicValue.SetVelocityX(0.0f);
			SetActiveFalse();
		}
	}
	if (UEngineInput::IsPress(VK_RIGHT)) {
		if (LogicValue.bIsMoveAble) {
			if (LogicValue.bIsGround) {
				float VelocityX = UEngineMath::Lerp(0.0f, 260.0f, UEngineMath::Clamp(UEngineInput::GetPressTime(VK_RIGHT) * 4.0f, 0.0f, 1.0f));
				LogicValue.SetVelocityX(VelocityX);
			}
		}
		if (!(LogicValue.bIsUsingSkill) && LogicValue.bIsGround) {
			Player->ChangeAnimation("Walk");
		}
	}
}

void ARightKey::SetActiveTrue()
{
	AActorFunction::SetActiveTrue();
	Player->SetActorRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));

}

void ARightKey::SetActiveFalse()
{
	AActorFunction::SetActiveFalse();

}