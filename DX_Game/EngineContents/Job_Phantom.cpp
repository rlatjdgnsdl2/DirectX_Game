#include "PreCompile.h"
#include "Job_Phantom.h"

#include "Player.h"

#include "PlayerFunction.h"



#include "Skill_UltimateDrive.h"
#include "Skill_SwiftPhantom.h"
#include "Skill_RiftBreak.h"
#include "Skill_DefyingFate.h"


UJob_Phantom::UJob_Phantom() 
{

	
	{
		ASkill_UltimateDrive* Skill = GetWorld()->SpawnActor<ASkill_UltimateDrive>().get();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill(EPlayer_Function::Ultimate_Drive, Skill);
	}

	{
		ASkill_SwiftPhantom* Skill = GetWorld()->SpawnActor<ASkill_SwiftPhantom>().get();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill(EPlayer_Function::Swift_Phantom, Skill);
	}


	{
		ASkill_RiftBreak* Skill = GetWorld()->SpawnActor<ASkill_RiftBreak>().get();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill(EPlayer_Function::Rift_Break, Skill);
	}

	{
		ASkill_DefyingFate* Skill = GetWorld()->SpawnActor<ASkill_DefyingFate>().get();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill(EPlayer_Function::Defying_Fate, Skill);
	}
}

UJob_Phantom::~UJob_Phantom() 
{
	
}
