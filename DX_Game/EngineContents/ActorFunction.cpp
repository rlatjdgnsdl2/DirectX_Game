#include "PreCompile.h"
#include "ActorFunction.h"


AActorFunction::AActorFunction() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
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
