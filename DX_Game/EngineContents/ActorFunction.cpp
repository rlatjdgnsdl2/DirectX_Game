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
	AActor* ActorPoint = Owner.lock().get();
	if (ActorPoint == nullptr) {
		MSGASSERT("SetOwner���ּ���");
	}
	AttachToActor(ActorPoint);
}
