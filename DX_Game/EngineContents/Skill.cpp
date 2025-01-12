#include "PreCompile.h"
#include "Skill.h"


ASkill::ASkill() 
{
	RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>();
}

ASkill::~ASkill() 
{

}

void ASkill::BeginPlay()
{
	AActor::BeginPlay();
	if (Owner == nullptr) {
		MSGASSERT("SetOwner���ּ���");
	}		
	AttachToActor(Owner);
}

void ASkill::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	Update(_DeltaTime);
}
