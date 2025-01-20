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

	if (UEngineInput::IsFree(VK_LEFT)) {
		SetActiveFalse();
	}
}

void ALeftKey::SetActiveTrue()
{
	AActorFunction::SetActiveTrue();
	Player->GetPlayerLogic().SetVelocityX(-100.0f);
}

void ALeftKey::SetActiveFalse()
{
	AActorFunction::SetActiveFalse();
	Player->GetPlayerLogic().SetVelocityX(0.0f);
}
