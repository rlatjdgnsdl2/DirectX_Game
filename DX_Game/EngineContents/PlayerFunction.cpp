#include "PreCompile.h"
#include "PlayerFunction.h"
#include "Player.h"


APlayerFunction::APlayerFunction() 
{

}

APlayerFunction::~APlayerFunction() 
{

}

void APlayerFunction::SetOwner(AActor* _Owner)
{
	AActorFunction::SetOwner(_Owner);
	Player = dynamic_cast<APlayer*>(Owner);

}


