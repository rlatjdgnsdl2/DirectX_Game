#include "PreCompile.h"
#include "ActorFunction.h"


AActorFunction::AActorFunction() 
{

}

AActorFunction::~AActorFunction() 
{

}

void AActorFunction::BeginPlay()
{
	AActor::BeginPlay();
	if (Owner == nullptr) {
		MSGASSERT("SetOwner���ּ���");
	}
	AttachToActor(Owner);
}
