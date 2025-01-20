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

	if (UEngineInput::IsUp) {
		SetActiveFalse();
	}
}

void ALeftKey::SetActiveTrue()
{
	AActorFunction::SetActiveTrue();
	Player.lock()->SetVelocityX(-100.0f);
}

void ALeftKey::SetActiveFalse()
{
	AActorFunction::SetActiveFalse();
	Player.lock()->SetVelocityX(0.0f);
}
