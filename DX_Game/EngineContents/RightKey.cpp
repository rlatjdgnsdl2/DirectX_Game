#include "PreCompile.h"
#include "RightKey.h"
#include "Player.h"


ARightKey::ARightKey() 
{

}

ARightKey::~ARightKey() 
{

}


void ARightKey::BeginPlay()
{
}

void ARightKey::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsUp) {
		SetActiveFalse();
	}
}

void ARightKey::SetActiveTrue()
{
	AActorFunction::SetActiveTrue();
	Player.lock()->SetVelocityX(-100.0f);
}

void ARightKey::SetActiveFalse()
{
	AActorFunction::SetActiveFalse();
	Player.lock()->SetVelocityX(0.0f);
}