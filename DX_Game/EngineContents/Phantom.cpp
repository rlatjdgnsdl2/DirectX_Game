#include "PreCompile.h"
#include "Phantom.h"

#include "Player.h"
#include "Skill_UltimateDrive.h"
#include "Skill_SwiftPhantom.h"


APhantom::APhantom() 
{
	{
		std::shared_ptr<ASkill_UltimateDrive> Skill = GetWorld()->SpawnActor<ASkill_UltimateDrive>();
		Skill->SetActiveFalse();
		InsertSkill("UltimateDrive", Skill);
	}

	{
		std::shared_ptr<ASkill_SwiftPhantom> Skill = GetWorld()->SpawnActor<ASkill_SwiftPhantom>();
		Skill->SetActiveFalse();
		InsertSkill("SwiftPhantom", Skill);
	}
}

APhantom::~APhantom() 
{
	
}
