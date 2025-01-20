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
		MSGASSERT("SetOwner해주세요");
	}
	AttachToActor(Owner);
}
