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

	if (UEngineInput::IsUp) {
		SetActiveFalse();
	}
}

void ARightKey::SetActiveTrue()
{
	AActorFunction::SetActiveTrue();
	
}

void ARightKey::SetActiveFalse()
{
	AActorFunction::SetActiveFalse();
	
}