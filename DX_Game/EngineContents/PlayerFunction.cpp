#include "PreCompile.h"
#include "PlayerFunction.h"
#include "Player.h"


APlayerFunction::APlayerFunction() 
{

}

APlayerFunction::~APlayerFunction() 
{

}

void APlayerFunction::SetOwner(std::shared_ptr<class AActor> _Owner)
{
	AActorFunction::SetOwner(_Owner);
	Player = std::static_pointer_cast<APlayer>(_Owner);
}


