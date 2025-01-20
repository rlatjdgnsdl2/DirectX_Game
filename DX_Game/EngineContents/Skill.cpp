#include "PreCompile.h"
#include "Skill.h"


ASkill::ASkill() 
{
	
}

ASkill::~ASkill() 
{

}

void ASkill::BeginPlay()
{
	APlayerFunction::BeginPlay();
	
}

void ASkill::Tick(float _DeltaTime)
{
	APlayerFunction::Tick(_DeltaTime);
	Update(_DeltaTime);
}
