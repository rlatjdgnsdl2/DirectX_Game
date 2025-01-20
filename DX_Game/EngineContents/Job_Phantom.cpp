#include "PreCompile.h"
#include "Job_Phantom.h"

#include "Player.h"
#include "Skill_UltimateDrive.h"
#include "Skill_SwiftPhantom.h"


UJob_Phantom::UJob_Phantom() 
{
	{
		std::shared_ptr<ASkill_UltimateDrive> Skill = GetWorld()->SpawnActor<ASkill_UltimateDrive>();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill("UltimateDrive", Skill);
	}

	{
		std::shared_ptr<ASkill_SwiftPhantom> Skill = GetWorld()->SpawnActor<ASkill_SwiftPhantom>();
		Skill->SetOwner(GetActor());
		Skill->SetActiveFalse();
		InsertSkill("SwiftPhantom", Skill);
	}
}

UJob_Phantom::~UJob_Phantom() 
{
	
}
